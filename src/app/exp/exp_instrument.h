/*
 * exp_measurement.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_EXP_EXP_INSTRUMENT_H_
#define SRC_APP_EXP_EXP_INSTRUMENT_H_

#define EXP_INSTRUMENT_SENSOR_COUNT 1

#include <stdint.h>

typedef enum {
    W470NM,
    W570NM,
    W630NM,
    W850NM,
    WNUM
} Exp_InstrumentWavelength;

void Exp_InstrumentInit();
void Exp_InstrumentLEDsOn(Exp_InstrumentWavelength wavelength);
void Exp_InstrumentLEDsOff(Exp_InstrumentWavelength wavelength);
void Exp_InstrumetToggleLEDs(Exp_InstrumentWavelength wavelength);
void Exp_InstrumentSetBrightness(Exp_InstrumentWavelength wavelength, uint8_t brightness);
void Exp_InstrumentRead(uint32_t buffer[EXP_INSTRUMENT_SENSOR_COUNT]);

#endif /* SRC_APP_EXP_EXP_INSTRUMENT_H_ */
