/*
 * mpq3326.c
 *
 *  Created on: Feb. 17, 2024
 *      Author: Ruben
 */

#include "mpq3326.h"

#define MPQ3326_REG_PWM_DIMMING_FREQ 0x00
#define MPQ3326_REG_CONTROL          0x01
#define MPQ3326_REG_CH_EN9TO16       0x04
#define MPQ3326_REG_CH_EN1TO8        0x05
#define MPQ3326_REG_CURRENT_LIMIT    0x0A
#define MPQ3326_CHANNELS             16

void MPQ3326_Init(SWI2C_Descriptor *descriptor) {
    SWI2C_Init(descriptor);

    uint8_t buffer[2];
    buffer[0] = MPQ3326_REG_CONTROL;
    buffer[1] = 1;
    SWI2C_Write(descriptor, buffer, 2);
}

void MPQ3326_TurnLEDsOn(SWI2C_Descriptor *descriptor) {
    uint8_t buffer[2];
    buffer[0] = MPQ3326_REG_CH_EN1TO8;
    buffer[1] = 0xFF;
    SWI2C_Write(descriptor, buffer, 2);

    buffer[0] = MPQ3326_REG_CH_EN9TO16;
    buffer[1] = 0xFF;
    SWI2C_Write(descriptor, buffer, 2);
}

void MPQ3326_TurnLEDsOff(SWI2C_Descriptor *descriptor) {
    uint8_t buffer[2];
    buffer[0] = MPQ3326_REG_CH_EN1TO8;
    buffer[1] = 0;
    SWI2C_Write(descriptor, buffer, 2);

    buffer[0] = MPQ3326_REG_CH_EN9TO16;
    buffer[1] = 0;
    SWI2C_Write(descriptor, buffer, 2);
}

void MPQ3326_SetBrightness(SWI2C_Descriptor *descriptor, uint8_t brightness) {
    uint8_t buffer[2];
    int i;
    for(i = 0; i < MPQ3326_CHANNELS; i ++) {
        buffer[0] = MPQ3326_REG_CURRENT_LIMIT + i;
        buffer[1] = brightness & 0x3F;
        SWI2C_Write(descriptor, buffer, 2);
    }
}
