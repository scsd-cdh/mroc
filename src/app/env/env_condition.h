/*
 * env_info.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_ENV_ENV_CONDITION_H_
#define SRC_APP_ENV_ENV_CONDITION_H_

#include <stdint.h>
#include <src/peripherals/bme280.h>
#include <src/peripherals/lmt01.h>

typedef struct
{
    uint16_t well_temperature;
    uint16_t ambient_temperature;
    uint16_t ambient_pressure;
    uint16_t ambient_humidity;
} Env_ConditionDescriptor;

#endif /* SRC_APP_ENV_ENV_CONDITION_H_ */
