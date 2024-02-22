/*
 * app.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

#include "hk/hk_condition.h"
#include "stdint.h"

typedef struct {
    uint32_t uptime_seconds;
} AppContext;

void App_Init();
uint32_t App_GetUptime();

#endif /* SRC_APP_APP_H_ */
