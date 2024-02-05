/*
 * thermistor.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_LMT01_H_
#define SRC_PERIPHERALS_LMT01_H_

#include <stdint.h>

typedef struct {
    uint8_t port;
    uint16_t pin;
}LMT01_Descriptor;

void LMT01_Init(LMT01_Descriptor *descriptor);
float LMT01_Read(LMT01_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_LMT01_H_ */
