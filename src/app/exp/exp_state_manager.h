/*
 * state_manager.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_STATE_MACHINE_STATE_MANAGER_H_
#define SRC_STATE_MACHINE_STATE_MANAGER_H_

#include "exp_state.h"
#include <stdbool.h>
#include <src/app/cmd/cmd_register.h>

typedef struct {
    // Experiment
    uint8_t last_state;
    uint32_t uptime_seconds;
    StateProgress progress;

    // Temperature
    uint16_t well_temperature;
    int32_t ambient_temperature;
    uint32_t ambient_pressure;
    uint32_t ambient_humidity;

    // Pumps
    bool bipump_on;
    uint32_t bipump_timer;
    bool pump_on;
    uint32_t pump_timer;

    // Valve
    bool valve_on;
}ExperimentMonitor;

void Exp_ExitState();
void Exp_Init();
void Exp_NextState();
void Exp_SetState(uint8_t newState);
void Exp_SetIdle();
void Exp_Update();

bool State_IsIdle();
void State_HandlePreparation();
void State_HandleActivation();
void State_HandleGrowth();
void State_HandleInduction();

#endif /* SRC_STATE_MACHINE_STATE_MANAGER_H_ */
