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
    uint8_t on_port;
    uint16_t on_pin;

    uint8_t direction_1_port;
    uint16_t direction_1_pin;

    uint8_t direction_2_port;
    uint16_t direction_2_pin;

    bool is_on;
    bool is_forward;
} Pump_Descriptor;

void Pump_Init(Pump_Descriptor *descriptor);
void Pump_Start(Pump_Descriptor *descriptor);
void Pump_Stop(Pump_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_PUMP_H_ */
