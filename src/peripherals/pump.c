/*
 * pump.c
 *
 *  Created on: Feb. 5, 2024
 *      Author: Ruben
 */

#include "pump.h"

void Pump_Init(Pump_Descriptor *descriptor) {
    GPIO_setAsOutputPin(
            descriptor->on_port,
            descriptor->on_pin
        );

    GPIO_setAsOutputPin(
            descriptor->direction_1_port,
            descriptor->direction_1_pin
        );

    GPIO_setAsOutputPin(
            descriptor->direction_2_port,
            descriptor->direction_2_pin
        );

    descriptor->is_on = false;
    descriptor->is_forward = true;
}

void Pump_Start(Pump_Descriptor *descriptor) {

}

void Pump_Stop(Pump_Descriptor *descriptor) {

}

