/*
 * exp_instrument.c
 *
 *  Created on: Feb. 25, 2024
 *      Author: Ruben
 */
#include "exp_instrument.h"
#include <src/config.h>
#include <src/drivers/drivers.h>

static SWI2C_Descriptor light_sensors[14];
static SWI2C_Descriptor w470nm;
static SWI2C_Descriptor w570nm;
static SWI2C_Descriptor w630nm;
static SWI2C_Descriptor w850nm;

void Exp_InstrumentInit() {
    w470nm.address = MPQ3326_W470_ADDR;
    w470nm.sda_port = MPQ3326_I2C_SDA_PORT;
    w470nm.sda_pin = MPQ3326_I2C_SDA_PIN;
    w470nm.scl_port = MPQ3326_I2C_SCL_PORT;
    w470nm.scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&w470nm);

    w570nm.address = MPQ3326_W570_ADDR;
    w570nm.sda_port = MPQ3326_I2C_SDA_PORT;
    w570nm.sda_pin = MPQ3326_I2C_SDA_PIN;
    w570nm.scl_port = MPQ3326_I2C_SCL_PORT;
    w570nm.scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&w570nm);

    w630nm.address = MPQ3326_W630_ADDR;
    w630nm.sda_port = MPQ3326_I2C_SDA_PORT;
    w630nm.sda_pin = MPQ3326_I2C_SDA_PIN;
    w630nm.scl_port = MPQ3326_I2C_SCL_PORT;
    w630nm.scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&w630nm);

    w850nm.address = MPQ3326_W850_ADDR;
    w850nm.sda_port = MPQ3326_I2C_SDA_PORT;
    w850nm.sda_pin = MPQ3326_I2C_SDA_PIN;
    w850nm.scl_port = MPQ3326_I2C_SCL_PORT;
    w850nm.scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&w850nm);
}

void Exp_InstrumentLEDsOn(Exp_InstrumentWavelength wavelength) {
    switch(wavelength) {
    case W470NM:
        MPQ3326_TurnLEDsOn(&w470nm);
        break;
    case W570NM:
        MPQ3326_TurnLEDsOn(&w570nm);
        break;
    case W630NM:
        MPQ3326_TurnLEDsOn(&w630nm);
        break;
    case W850NM:
        MPQ3326_TurnLEDsOn(&w850nm);
        break;
    }
}

void Exp_InstrumentLEDsOff(Exp_InstrumentWavelength wavelength) {
    switch(wavelength) {
    case W470NM:
        MPQ3326_TurnLEDsOff(&w470nm);
        break;
    case W570NM:
        MPQ3326_TurnLEDsOff(&w570nm);
        break;
    case W630NM:
        MPQ3326_TurnLEDsOff(&w630nm);
        break;
    case W850NM:
        MPQ3326_TurnLEDsOff(&w850nm);
        break;
    }
}

void Exp_InstrumentSetBrightness(Exp_InstrumentWavelength wavelength, uint8_t brightness) {
    switch(wavelength) {
    case W470NM:
        MPQ3326_SetBrightness(&w470nm);
        break;
    case W570NM:
        MPQ3326_SetBrightness(&w570nm);
        break;
    case W630NM:
        MPQ3326_SetBrightness(&w630nm);
        break;
    case W850NM:
        MPQ3326_SetBrightness(&w850nm);
        break;
    }
}

void Exp_InstrumentRead(uint32_t buffer[14]) {
    for(uint8_t i = 0; i < 14; i ++) {

    }
}
