/*
 * pump.c
 *
 *  Created on: Feb. 5, 2024
 *      Author: Ruben & Jon & Shen (Elec god)
 */

#include "pump.h"

void Pump_Init(Pump_Descriptor *descriptor) {
    GPIO_setAsOutputPin(
          descriptor->port,
          descriptor->pin
      );
    descriptor->is_on = false;

}

void  Pump_TurnOn(Pump_Descriptor *descriptor) {
    GPIO_setOutputLowOnPin(
        descriptor->port,
        descriptor->pin
    );
    descriptor->is_on = true;

}

void Pump_TurnOff(Pump_Descriptor *descriptor) {
    GPIO_setOutputHighOnPin(
            descriptor->port,
            descriptor->pin
        );
        descriptor->is_on = false;
}

