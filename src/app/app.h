/*
 * app.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

#include "env/env_condition.h"
#include "hk/hk_condition.h"
#include "stdint.h"

typedef struct {
    uint32_t uptime_seconds;
    Hk_ConditionDescriptor housekeepingCondition;
    Env_ConditionDescriptor environmentCondition;
} AppContext;

void App_Init();
uint32_t App_GetUptime();

#endif /* SRC_APP_APP_H_ */
