/*
 * heater.c
 *
 *  Created on: Feb. 25, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_HEATER_C_
#define SRC_PERIPHERALS_HEATER_C_

#include "heater.h"
#include <src/drivers/drivers.h>

void Heater_Init(Heater_Descriptor *descriptor) {
    GPIO_setAsOutputPin(
          descriptor->port,
          descriptor->pin
      );

}

void Heater_On(Heater_Descriptor *descriptor) {
    GPIO_setOutputLowOnPin(
        descriptor->port,
        descriptor->pin
    );

}

void Heater_Off(Heater_Descriptor *descriptor) {
    GPIO_setOutputHighOnPin(
        descriptor->port,
        descriptor->pin
    );
}


#endif /* SRC_PERIPHERALS_HEATER_C_ */
