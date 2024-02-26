/*
 * heater.h
 *
 *  Created on: Feb. 25, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_HEATER_H_
#define SRC_PERIPHERALS_HEATER_H_

typedef struct {
       uint8_t     port;
       uint16_t    pin;
} Heater_Descriptor;

void Heater_Init(Heater_Descriptor *descriptor);
void Heater_On(Heater_Descriptor *descriptor);
void Heater_Off(Heater_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_HEATER_H_ */
