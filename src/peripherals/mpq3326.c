/*
 * mpq3326.c
 *
 *  Created on: Feb. 17, 2024
 *      Author: Ruben
 */

#include "mpq3326.h"

#define MPQ3326_EN_REG_9TO16    0x04
#define MPQ3326_EN_REG_1TO8     0x05

void MPQ3326_Init(SWI2C_Descriptor *descriptor) {
    SWI2C_Init(descriptor);
}

void MPQ3326_TurnLEDsOn(SWI2C_Descriptor *descriptor) {

}

void MPQ3326_TurnLEDsOff(SWI2C_Descriptor *descriptor) {

}

void MPQ3326_SetBrightness(SWI2C_Descriptor *descriptor) {

}
