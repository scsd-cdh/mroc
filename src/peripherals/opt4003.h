/*
 * opt4003-q1.h
 *
 *  Created on: Feb. 18, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_OPT4003_H_
#define SRC_PERIPHERALS_OPT4003_H_

#include <stdint.h>
#include <stdbool.h>
#include <src/drivers/swi2c.h>

void OPT4003_Init(SWI2C_Descriptor *descriptor);
bool OPT4003_Read(SWI2C_Descriptor *descriptor, uint32_t *lux);

#endif /* SRC_PERIPHERALS_OPT4003_H_ */
