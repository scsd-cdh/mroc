/*
 * state_manager.c
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#include "exp_state_manager.h"
#include <src/drivers/drivers.h>
#include <src/app/app.h>

static uint8_t currentState;
static ExperimentMonitor experimentMonitor;

void Exp_Init()
{
    currentState = STATE_IDLE;

    experimentMonitor.last_state = STATE_IDLE;
    experimentMonitor.uptime_seconds = App_GetUptime();
    experimentMonitor.progress = STATE_COMPLETE;
}

void Exp_NextState()
{
    currentState = experimentMonitor.last_state + 1;
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
        experimentMonitor.last_state = currentState;
        experimentMonitor.uptime_seconds = App_GetUptime() - experimentMonitor.uptime_seconds;
    }

    currentState = STATE_IDLE;
}

void Exp_Update()
{
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

    Cmd_SetSystemStatus(currentState, App_GetUptime());
    Cmd_SetExperimentStatusRegister(experimentMonitor.last_state, experimentMonitor.progress, experimentMonitor.uptime_seconds);
}

bool State_IsIdle() {
    return currentState == STATE_IDLE;
}

void State_HandlePreparation()
{
    // Turn LEDs OFF

    // if (ctx->well_temperature > 20.0 && ctx->ambient_temperature > 20.0)
    // {
    // Turn pump #1 on
    // Start timer for x period
    // }
}

void State_HandleActivation()
{
    // Valve on
    // Turn pump #2 on
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
