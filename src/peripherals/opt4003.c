/*
 * opt4003-q1.c
 *
 *  Created on: Feb. 18, 2024
 *      Author: Ruben
 */

#include "opt4003.h"

void OPT4003_Init(SWI2C_Descriptor *descriptor) {
    SWI2C_Init(descriptor);
    // TODO: Add continuous mode
}

int64_t OPT4003_Read(SWI2C_Descriptor *descriptor) {
    int64_t lux = 0;
    return lux;
}

