/*
 * lmt01.c
 *
 *  Created on: Feb 5, 2024
 *      Author: space
 */

static uint16_t pulseCount = 0;
static uint16_t recordedPulseCount = 0;

void LMT01_Init(LMT01_Descriptor *descriptor) {
    // TODO: Use some sort of timer
}

float LMT01_Read(LMT01_Descriptor *descriptor) {
    return ((float)recordedPulseCount/4096.0f*256.0f)-50.0f;
}

