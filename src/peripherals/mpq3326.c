/*
 * mpq3326.c
 *
 *  Created on: Feb. 17, 2024
 *      Author: Ruben
 */

#include "mpq3326.h"

void MPQ3326_Init(SWI2C_Descriptor *descriptor) {
    SWI2C_Init(descriptor);
}

void MPQ3326_Write(SWI2C_Descriptor *descriptor, uint16_t leds) {
    uint8_t buffer[3];

    buffer[0] = 0x04;
    buffer[1] = leds & 0xFF;
    SWI2C_Write(descriptor, buffer, 2);

    buffer[0] = 0x05;
    buffer[1] = (leds >> 8) & 0xFF;
    SWI2C_Write(descriptor, buffer, 2);
}
