/*
 * state_manager.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_STATE_MACHINE_STATE_MANAGER_H_
#define SRC_STATE_MACHINE_STATE_MANAGER_H_

#include "exp_measurement.h"
#include "exp_state.h"
#include <stdbool.h>
#include <src/app/cmd/cmd_register.h>

typedef struct {
    uint8_t last_state;
    uint32_t uptime_seconds;
    StateProgress progress;
}ExperimentMonitor;

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
