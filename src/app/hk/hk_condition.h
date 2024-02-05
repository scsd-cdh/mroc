/*
 * hk_condition.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_HK_HK_CONDITION_H_
#define SRC_APP_HK_HK_CONDITION_H_

#include <stdint.h>

typedef struct
{
    uint16_t pump_current_sensing;
    uint16_t heater_current_sensing;
    uint16_t voltage_reference_current_sensing;
} Hk_ConditionDescriptor;

#endif /* SRC_APP_HK_HK_CONDITION_H_ */
