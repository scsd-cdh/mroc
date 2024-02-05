/*
 * bipump.h
 *
 *  Created on: Feb 5, 2024
 *      Author: space
 */

#ifndef SRC_PERIPHERALS_BIPUMP_H_
#define SRC_PERIPHERALS_BIPUMP_H_

typedef enum{
    FORWARD,
    BACKWARD,
    OFF
}Bipump_State;

typedef struct{
    uint8_t pump_forward_p_port;
    uint16_t pump_forward_p_pin;
    uint8_t pump_forward_n_port;
    uint16_t pump_forward_n_pin;
    uint8_t pump_backward_p_port;
    uint16_t pump_backward_p_pin;
    uint8_t pump_backward_n_port;
    uint16_t pump_backward_n_pin;
    Bipump_State state;
}Bipump_Descriptor;


#endif /* SRC_PERIPHERALS_BIPUMP_H_ */
