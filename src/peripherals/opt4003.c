/*
 * opt4003-q1.c
 *
 *  Created on: Feb. 18, 2024
 *      Author: Ruben
 */

#include "opt4003.h"

#define OPT4003_REG_ENABLE      0x0A
#define OPT4003_REG_CH0         0x00
#define OPT4003_REG_CH1         0x02

void OPT4003_Init(SWI2C_Descriptor *descriptor) {
    SWI2C_Init(descriptor);

    uint8_t buffer[3];
    buffer[0] = OPT4003_REG_ENABLE;
    buffer[1] = 0b00110010;
    buffer[2] = 0b00111000;
    SWI2C_Write(descriptor, buffer, 3);
}

bool OPT4003_Read(SWI2C_Descriptor *descriptor, uint32_t *lux) {
    uint8_t buffer[4];
    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;

    buffer[0] = OPT4003_REG_CH0;
    SWI2C_Write(descriptor, buffer, 1);
    int32_t bytes_read = SWI2C_Read(descriptor, buffer, 4);

    if(bytes_read != 4) {
        return false;
    }

    uint8_t exponent = buffer[0] >> 4;
    uint16_t msb = ((buffer[0] & 0x0F) << 8) | buffer[1];
    uint16_t lsb = buffer[2];

    uint32_t mantissa = (msb << 8) + lsb;
    uint32_t adc_codes = mantissa << exponent;
    *lux = adc_codes * 535E-6;

    return true;
}
