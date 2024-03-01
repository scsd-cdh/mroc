/*
 * valve.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_VALVE_H_
#define SRC_PERIPHERALS_VALVE_H_

#include <stdint.h>

typedef struct {
    uint8_t     port;
    uint16_t    pin;
} Valve_Descriptor;

void Valve_Init(Valve_Descriptor *descriptor);
void Valve_Open(Valve_Descriptor *descriptor);
void Valve_Close(Valve_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_VALVE_H_ */
