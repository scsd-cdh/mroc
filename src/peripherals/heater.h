/*
 * heater.h
 *
 *  Created on: Feb. 25, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_HEATER_H_
#define SRC_PERIPHERALS_HEATER_H_

#include <stdint.h>

typedef struct {
       uint8_t     port;
       uint16_t    pin;
} Heater_Descriptor;

void Heater_Init(Heater_Descriptor *descriptor);
void Heater_Write(uint8_t value);
void Heater_Off();

#endif /* SRC_PERIPHERALS_HEATER_H_ */
