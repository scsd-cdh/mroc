/*
 * state_manager.c
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#include "exp_state_manager.h"
#include <src/config.h>
#include <src/drivers/drivers.h>
#include <src/app/app.h>
#include <src/peripherals/lmt01.h>
#include <src/peripherals/pump.h>
#include <src/peripherals/bipump.h>
#include <src/peripherals/bme280.h>
#include <src/peripherals/valve.h>

static BME280_Descriptor ambientConditionDescriptor;
static LMT01_Descriptor wellTemperatureDescriptor;
static Pump_Descriptor pumpDescriptor;
static Bipump_Descriptor bipumpDescriptor;
static Valve_Descriptor valveDescriptor;

static uint8_t currentState;
static ExperimentMonitor experimentMonitor;

void Exp_Init()
{
    // Initialize experiment monitors
    currentState = STATE_IDLE;

    experimentMonitor.last_state = STATE_IDLE;
    experimentMonitor.uptime_seconds = App_GetUptime();
    experimentMonitor.progress = STATE_COMPLETE;

    // BME280 Initialize (Ambient temperature, pressure, humidity)

    // LMT01 Initialize (Well temperature)
    wellTemperatureDescriptor.port = LMT01_PORT;
    wellTemperatureDescriptor.pin = LMT01_PIN;
    LMT01_Init(&wellTemperatureDescriptor);

    // Pump Initialize (Feeding pump)
    pumpDescriptor.port = PUMP_PORT;
    pumpDescriptor.pin = PUMP_PIN;
    Pump_Init(&pumpDescriptor);

    // Valve initialize (Feeding valve)
    valveDescriptor.port = VALVE_PORT;
    valveDescriptor.pin = VALVE_PIN;
    Valve_Init(&valveDescriptor);

    // Bipump Initialize (Mixing pump)
    bipumpDescriptor.pump_forward_p_port = BIPUMP_FORWARD_P_PORT;
    bipumpDescriptor.pump_forward_p_pin = BIPUMP_FORWARD_P_PIN;
    bipumpDescriptor.pump_forward_n_port = BIPUMP_FORWARD_N_PORT;
    bipumpDescriptor.pump_forward_n_pin = BIPUMP_FORWARD_N_PIN;
    bipumpDescriptor.pump_backward_p_port = BIPUMP_BACKWARD_P_PORT;
    bipumpDescriptor.pump_backward_p_pin = BIPUMP_BACKWARD_P_PIN;
    bipumpDescriptor.pump_backward_n_port = BIPUMP_BACKWARD_N_PORT;
    bipumpDescriptor.pump_backward_n_pin = BIPUMP_BACKWARD_N_PIN;
    Bipump_Init(&bipumpDescriptor);

    // Initialize spectrophotometer

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
    // Update state
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
    Cmd_SetExperimentStatusRegister(experimentMonitor.last_state, experimentMonitor.progress, experimentMonitor.uptime_seconds);
}

bool State_IsIdle() {
    return currentState == STATE_IDLE;
}

void State_HandlePreparation()
{
    if (
            experimentMonitor.well_temperature > MIN_EXP_TEMP &&
            experimentMonitor.ambient_temperature > MIN_EXP_TEMP &&
            !experimentMonitor.bipump_on) {
        Bipump_Forward(&bipumpDescriptor);
        experimentMonitor.bipump_timer = App_GetUptime(); // Start timer
    }

    if(experimentMonitor.bipump_on && App_GetUptime() - experimentMonitor.bipump_timer >= MIX_PUMP_DURATION) {
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
        Pump_On(&pumpDescriptor);
        experimentMonitor.pump_timer = App_GetUptime(); // Start timer
    }

    if (experimentMonitor.valve_on && App_GetUptime() - experimentMonitor.pump_timer >= MIX_PUMP_DURATION) {
        Pump_Off(&pumpDescriptor);
        Valve_Close(&valveDescriptor);

        experimentMonitor.last_state = currentState;
        experimentMonitor.progress = STATE_COMPLETE;
        experimentMonitor.uptime_seconds = App_GetUptime() - experimentMonitor.uptime_seconds;

        currentState = STATE_IDLE;
    }
}

void State_HandleGrowth()
{
    // Turn green LEDs on
    // Read values
    // Turn green LEDs off

    // Turn infrared LEDs on
    // Read values
    // Turn infrared LEDs off
}

void State_HandleInduction()
{
    // Turn blue LEDs on
    // Read values
    // Turn blue LEDs off
}
