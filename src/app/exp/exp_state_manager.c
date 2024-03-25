/*
 * state_manager.c
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#include "exp_state_manager.h"
#include "exp_instrument.h"
#include <src/config.h>
#include <src/drivers/drivers.h>
#include <src/app/app.h>
#include <src/app/hk/hk_condition.h>
#include <src/peripherals/lmt01.h>
#include <src/peripherals/pump.h>
#include <src/peripherals/bipump.h>
#include <src/peripherals/bme280.h>
#include <src/peripherals/valve.h>
#include <src/peripherals/heater.h>

static Hk_ConditionDescriptor hkDescriptor;

static BME280_Descriptor ambientConditionDescriptor;
static LMT01_Descriptor wellTemperatureDescriptor;
static Pump_Descriptor pumpDescriptor;
static Bipump_Descriptor bipumpDescriptor;
static Valve_Descriptor valveDescriptor;
static Heater_Descriptor heaterDescriptor;

static uint8_t currentState;
static ExperimentMonitor experimentMonitor;
static InstrumentState instrumentState;
static Exp_InstrumentWavelength currentWavelength;

static uint16_t currentSensing = 0;

static uint32_t experimentResults[14];

void Exp_Init()
{
    // Initialize experiment monitors
    currentState = STATE_IDLE;

    experimentMonitor.last_state = STATE_IDLE;
    experimentMonitor.uptime_seconds = App_GetUptime();
    experimentMonitor.progress = STATE_COMPLETE;

    instrumentState = INS_INIT;
    currentWavelength = W470NM;

    // Spectrophotometer Initialize (All LEDs and sensors)
    Exp_InstrumentInit();

    // BME280 Initialize (Ambient temperature, pressure, humidity)

    // LMT01 Initialize (Well temperature)
    wellTemperatureDescriptor.port = LMT01_PORT;
    wellTemperatureDescriptor.pin = LMT01_PIN;
    LMT01_Init(&wellTemperatureDescriptor);

    // Pump Initialize (Feeding pump)
    pumpDescriptor.port = PUMP_PORT;
    pumpDescriptor.pin = PUMP_PIN;
    Pump_Init(&pumpDescriptor);

    // Bipump Initialize (Mixing pump)
    bipumpDescriptor.pump_q5_port = BIPUMP_Q5_PORT;
    bipumpDescriptor.pump_q5_pin = BIPUMP_Q5_PIN;
    bipumpDescriptor.pump_q6_port = BIPUMP_Q6_PORT;
    bipumpDescriptor.pump_q6_pin = BIPUMP_Q6_PIN;
    bipumpDescriptor.pump_q1_port = BIPUMP_Q1_PORT;
    bipumpDescriptor.pump_q1_pin = BIPUMP_Q1_PIN;
    bipumpDescriptor.pump_q2_port = BIPUMP_Q2_PORT;
    bipumpDescriptor.pump_q2_pin = BIPUMP_Q2_PIN;
    Bipump_Init(&bipumpDescriptor);

    // Valve initialize (Feeding valve)
    valveDescriptor.port = VALVE_PORT;
    valveDescriptor.pin = VALVE_PIN;
    Valve_Init(&valveDescriptor);

    // Heater Initialize
    heaterDescriptor.port = HEATER_PORT;
    heaterDescriptor.pin = HEATER_PIN;
    Heater_Init(&heaterDescriptor);

    // Housekeeping Initialize
    HK_ConditionInit(&hkDescriptor);
}

void Exp_NextState()
{
    currentState = experimentMonitor.last_state + 1;
    experimentMonitor.last_state = currentState;
    experimentMonitor.uptime_seconds = App_GetUptime();
    experimentMonitor.progress = STATE_INCOMPLETE;
}

void Exp_SetState(uint8_t newState)
{
    currentState = newState;

    if(currentState != STATE_IDLE) {
        experimentMonitor.last_state = newState;
        experimentMonitor.uptime_seconds = App_GetUptime();
        experimentMonitor.progress = STATE_INCOMPLETE;
    }
}

void Exp_SetIdle() {
    if (currentState != STATE_IDLE) {
        experimentMonitor.uptime_seconds = App_GetUptime() - experimentMonitor.uptime_seconds;
    }

    currentState = STATE_IDLE;
}

void Exp_Update()
{
    HK_Update();
    HK_Read(&hkDescriptor);

    experimentMonitor.well_temperature = LMT01_Read(&wellTemperatureDescriptor);

    // Do experiment actions
    switch(currentState) {
    case STATE_PREPARATION:
        State_HandlePreparation();
        break;
    case STATE_ACTIVATION:
        State_HandleActivation();
        break;
    case STATE_GROWTH:
        State_HandlePreparation();
        break;
    case STATE_INDUCTION:
        State_HandleInduction();
        break;
    default:
        break;
    }

    // Update Registers
    Cmd_SetSystemStatus(currentState, App_GetUptime());
    Cmd_SetExperimentStatusRegister(
            experimentMonitor.last_state,
            experimentMonitor.progress,
            experimentMonitor.uptime_seconds);
    Cmd_SetEnvironmentInformationRegister(
            experimentMonitor.well_temperature,
            experimentMonitor.ambient_temperature,
            experimentMonitor.ambient_pressure,
            experimentMonitor.ambient_humidity
    );
    Cmd_SetPhotosensorResults(experimentResults);
}

bool State_IsIdle() {
    return currentState == STATE_IDLE;
}

void State_HandlePreparation()
{
    if (experimentMonitor.well_temperature > MIN_EXP_TEMP &&
        experimentMonitor.ambient_temperature > MIN_EXP_TEMP &&
        !experimentMonitor.bipump_on) {
        Bipump_Forward(&bipumpDescriptor);
        experimentMonitor.bipump_timer = App_GetUptime(); // Start timer
    }

    if(experimentMonitor.bipump_on &&
        App_GetUptime() - experimentMonitor.bipump_timer >= MIX_PUMP_DURATION) {
        Bipump_Off(&bipumpDescriptor);

        experimentMonitor.last_state = currentState;
        experimentMonitor.progress = STATE_COMPLETE;
        experimentMonitor.uptime_seconds = App_GetUptime() - experimentMonitor.uptime_seconds;

        currentState = STATE_IDLE;
    }
}

void State_HandleActivation()
{
    if (!experimentMonitor.valve_on) {
        Valve_Open(&valveDescriptor);
        __delay_cycles(100);
        Pump_On(&pumpDescriptor);
        experimentMonitor.pump_timer = App_GetUptime(); // Start timer
    }

    if (experimentMonitor.valve_on &&
        App_GetUptime() - experimentMonitor.pump_timer >= MIX_PUMP_DURATION) {
        Pump_Off(&pumpDescriptor);
        __delay_cycles(100);
        Valve_Close(&valveDescriptor);

        experimentMonitor.last_state = currentState;
        experimentMonitor.progress = STATE_COMPLETE;
        experimentMonitor.uptime_seconds = App_GetUptime() - experimentMonitor.uptime_seconds;

        currentWavelength = W630NM;

        currentState = STATE_IDLE;
    }
}

void State_HandleGrowth()
{
    switch(instrumentState) {
    case INS_INIT:
        instrumentState = INS_ON;
        break;
    case INS_ON:
        Exp_InstrumentLEDsOn(currentWavelength);
        instrumentState = INS_CAPTURE;
        break;
    case INS_OFF:
        // For redundancy sake turn them all off.
        Exp_InstrumentLEDsOff(W470NM);
        Exp_InstrumentLEDsOff(W570NM);
        Exp_InstrumentLEDsOff(W630NM);
        Exp_InstrumentLEDsOff(W850NM);
        instrumentState = INS_ON;

        // Alternate between W630NM and W850NM
        if (currentWavelength == W630NM) {
            currentWavelength = W850NM;
        } else {
            currentWavelength = W630NM;
        }
        break;
    case INS_CAPTURE:
        Exp_InstrumentRead(experimentResults);
        instrumentState = INS_OFF;
        break;
    default:
        instrumentState = INS_INIT;
        break;
    }
}

void State_HandleInduction()
{
    switch(instrumentState) {
        case INS_INIT:
            instrumentState = INS_ON;
            break;
        case INS_ON:
            Exp_InstrumentLEDsOn(W470NM);
            instrumentState = INS_CAPTURE;
            break;
        case INS_OFF:
            // For redundancy sake turn them all off.
            Exp_InstrumentLEDsOff(W470NM);
            Exp_InstrumentLEDsOff(W570NM);
            Exp_InstrumentLEDsOff(W630NM);
            Exp_InstrumentLEDsOff(W850NM);
            instrumentState = INS_ON;
            break;
        case INS_CAPTURE:
            Exp_InstrumentRead(experimentResults);
            instrumentState = INS_OFF;
            break;
        default:
            instrumentState = INS_INIT;
            break;
        }
}
