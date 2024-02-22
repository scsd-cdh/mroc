/*
 * mpq3326.h
 *
 *  Created on: Feb. 17, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_MPQ3326_H_
#define SRC_PERIPHERALS_MPQ3326_H_

#include <stdint.h>
#include <src/drivers/swi2c.h>

void MPQ3326_Init(SWI2C_Descriptor *descriptor);
void MPQ3326_Write(SWI2C_Descriptor *descriptor, uint16_t leds);

#endif /* SRC_PERIPHERALS_MPQ3326_H_ */
