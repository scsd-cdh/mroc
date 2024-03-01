/*
 * pump.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_PUMP_H_
#define SRC_PERIPHERALS_PUMP_H_

#include <stdint.h>

typedef struct {
       uint8_t     port;
       uint16_t    pin;
} Pump_Descriptor;

void Pump_Init(Pump_Descriptor *descriptor);
void Pump_On(Pump_Descriptor *descriptor);
void Pump_Off(Pump_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_PUMP_H_ */
