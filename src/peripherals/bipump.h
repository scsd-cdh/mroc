/*
 * bipump.h
 *
 *  Created on: Feb 5, 2024
 *      Author: space
 */

#ifndef SRC_PERIPHERALS_BIPUMP_H_
#define SRC_PERIPHERALS_BIPUMP_H_

#include <stdint.h>

typedef enum{
    FORWARD,
    BACKWARD,
    OFF
}Bipump_State;

typedef struct{
    uint8_t pump_q1_port;
    uint16_t pump_q1_pin;
    uint8_t pump_q2_port;
    uint16_t pump_q2_pin;
    uint8_t pump_q5_port;
    uint16_t pump_q5_pin;
    uint8_t pump_q6_port;
    uint16_t pump_q6_pin;
    Bipump_State state;
}Bipump_Descriptor;

void Bipump_Init(Bipump_Descriptor *descriptor);
void Bipump_Forward(Bipump_Descriptor *descriptor);
void Bipump_Backward(Bipump_Descriptor *descriptor);
void Bipump_Off(Bipump_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_BIPUMP_H_ */
