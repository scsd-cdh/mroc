/*
 * pump.c
 *
 *  Created on: Feb. 5, 2024
 *      Author: Ruben & Jon & Shen (Elec god)
 */

#include "pump.h"
#include <src/drivers/drivers.h>

void Pump_Init(Pump_Descriptor *descriptor) {
    GPIO_setAsOutputPin(
          descriptor->port,
          descriptor->pin
      );
}

void Pump_On(Pump_Descriptor *descriptor) {
    GPIO_setOutputLowOnPin(
        descriptor->port,
        descriptor->pin
    );
}

void Pump_Off(Pump_Descriptor *descriptor) {
    GPIO_setOutputHighOnPin(
        descriptor->port,
        descriptor->pin
    );
}
