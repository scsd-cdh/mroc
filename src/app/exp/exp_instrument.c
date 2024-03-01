/*
 * exp_instrument.c
 *
 *  Created on: Feb. 25, 2024
 *      Author: Ruben
 */
#include "exp_instrument.h"
#include <src/config.h>
#include <src/drivers/drivers.h>
#include <src/peripherals/mpq3326.h>
#include <src/peripherals/opt4003.h>
#include <stdbool.h>

static SWI2C_Descriptor light_sensors[EXP_INSTRUMENT_SENSOR_COUNT];

static bool wavelength_state[WNUM];
static SWI2C_Descriptor wavelength_descriptors[WNUM];

void Exp_InstrumentInit() {
    wavelength_state[W470NM] = false;
    wavelength_state[W570NM] = false;
    wavelength_state[W630NM] = false;
    wavelength_state[W850NM] = false;

    wavelength_descriptors[W470NM].address = MPQ3326_W470_ADDR;
    wavelength_descriptors[W470NM].sda_port = MPQ3326_I2C_SDA_PORT;
    wavelength_descriptors[W470NM].sda_pin = MPQ3326_I2C_SDA_PIN;
    wavelength_descriptors[W470NM].scl_port = MPQ3326_I2C_SCL_PORT;
    wavelength_descriptors[W470NM].scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&wavelength_descriptors[W470NM]);

    wavelength_descriptors[W570NM].address = MPQ3326_W570_ADDR;
    wavelength_descriptors[W570NM].sda_port = MPQ3326_I2C_SDA_PORT;
    wavelength_descriptors[W570NM].sda_pin = MPQ3326_I2C_SDA_PIN;
    wavelength_descriptors[W570NM].scl_port = MPQ3326_I2C_SCL_PORT;
    wavelength_descriptors[W570NM].scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&wavelength_descriptors[W570NM]);

    wavelength_descriptors[W630NM].address = MPQ3326_W630_ADDR;
    wavelength_descriptors[W630NM].sda_port = MPQ3326_I2C_SDA_PORT;
    wavelength_descriptors[W630NM].sda_pin = MPQ3326_I2C_SDA_PIN;
    wavelength_descriptors[W630NM].scl_port = MPQ3326_I2C_SCL_PORT;
    wavelength_descriptors[W630NM].scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&wavelength_descriptors[W630NM]);

    wavelength_descriptors[W850NM].address = MPQ3326_W850_ADDR;
    wavelength_descriptors[W850NM].sda_port = MPQ3326_I2C_SDA_PORT;
    wavelength_descriptors[W850NM].sda_pin = MPQ3326_I2C_SDA_PIN;
    wavelength_descriptors[W850NM].scl_port = MPQ3326_I2C_SCL_PORT;
    wavelength_descriptors[W850NM].scl_pin = MPQ3326_I2C_SCL_PIN;
    MPQ3326_Init(&wavelength_descriptors[W850NM]);

    MPQ3326_TurnLEDsOff(&wavelength_descriptors[W470NM]);
    MPQ3326_TurnLEDsOff(&wavelength_descriptors[W570NM]);
    MPQ3326_TurnLEDsOff(&wavelength_descriptors[W630NM]);
    MPQ3326_TurnLEDsOff(&wavelength_descriptors[W850NM]);

//    light_sensors[0].address = OPT4003_I2C_ADDR_4;
//    light_sensors[0].sda_port = OPT4003_I2C_SDA_3_PORT;
//    light_sensors[0].sda_pin = OPT4003_I2C_SDA_3_PIN;
//    light_sensors[0].scl_port = OPT4003_I2C_SCL_3_PORT;
//    light_sensors[0].scl_pin = OPT4003_I2C_SCL_3_PIN;
//    OPT4003_Init(&light_sensors[0]);
//
//    light_sensors[1].address = OPT4003_I2C_ADDR_1;
//    light_sensors[1].sda_port = OPT4003_I2C_SDA_3_PORT;
//    light_sensors[1].sda_pin = OPT4003_I2C_SDA_3_PIN;
//    light_sensors[1].scl_port = OPT4003_I2C_SCL_3_PORT;
//    light_sensors[1].scl_pin = OPT4003_I2C_SCL_3_PIN;
//    OPT4003_Init(&light_sensors[1]);
//
//    light_sensors[2].address = OPT4003_I2C_ADDR_3;
//    light_sensors[2].sda_port = OPT4003_I2C_SDA_3_PORT;
//    light_sensors[2].sda_pin = OPT4003_I2C_SDA_3_PIN;
//    light_sensors[2].scl_port = OPT4003_I2C_SCL_3_PORT;
//    light_sensors[2].scl_pin = OPT4003_I2C_SCL_3_PIN;
//    OPT4003_Init(&light_sensors[2]);

    light_sensors[0].address = OPT4003_I2C_ADDR_2;
    light_sensors[0].sda_port = MPQ3326_I2C_SDA_PORT;
    light_sensors[0].sda_pin = MPQ3326_I2C_SDA_PIN;
    light_sensors[0].scl_port = MPQ3326_I2C_SCL_PORT;
    light_sensors[0].scl_pin = MPQ3326_I2C_SCL_PIN;
    OPT4003_Init(&light_sensors[0]);

//    light_sensors[4].address = OPT4003_I2C_ADDR_4;
//    light_sensors[4].sda_port = OPT4003_I2C_SDA_1_PORT;
//    light_sensors[4].sda_pin = OPT4003_I2C_SDA_1_PIN;
//    light_sensors[4].scl_port = OPT4003_I2C_SCL_1_PORT;
//    light_sensors[4].scl_pin = OPT4003_I2C_SCL_1_PIN;
//    OPT4003_Init(&light_sensors[4]);
//
//    light_sensors[5].address = OPT4003_I2C_ADDR_3;
//    light_sensors[5].sda_port = OPT4003_I2C_SDA_1_PORT;
//    light_sensors[5].sda_pin = OPT4003_I2C_SDA_1_PIN;
//    light_sensors[5].scl_port = OPT4003_I2C_SCL_1_PORT;
//    light_sensors[5].scl_pin = OPT4003_I2C_SCL_1_PIN;
//    OPT4003_Init(&light_sensors[5]);
//
//    light_sensors[6].address = OPT4003_I2C_ADDR_2;
//    light_sensors[6].sda_port = OPT4003_I2C_SDA_1_PORT;
//    light_sensors[6].sda_pin = OPT4003_I2C_SDA_1_PIN;
//    light_sensors[6].scl_port = OPT4003_I2C_SCL_1_PORT;
//    light_sensors[6].scl_pin = OPT4003_I2C_SCL_1_PIN;
//    OPT4003_Init(&light_sensors[6]);
//
//    light_sensors[7].address = OPT4003_I2C_ADDR_1;
//    light_sensors[7].sda_port = OPT4003_I2C_SDA_1_PORT;
//    light_sensors[7].sda_pin = OPT4003_I2C_SDA_1_PIN;
//    light_sensors[7].scl_port = OPT4003_I2C_SCL_1_PORT;
//    light_sensors[7].scl_pin = OPT4003_I2C_SCL_1_PIN;
//    OPT4003_Init(&light_sensors[7]);
//
//    light_sensors[8].address = OPT4003_I2C_ADDR_2;
//    light_sensors[8].sda_port = OPT4003_I2C_SDA_2_PORT;
//    light_sensors[8].sda_pin = OPT4003_I2C_SDA_2_PIN;
//    light_sensors[8].scl_port = OPT4003_I2C_SCL_2_PORT;
//    light_sensors[8].scl_pin = OPT4003_I2C_SCL_2_PIN;
//    OPT4003_Init(&light_sensors[8]);
//
//    light_sensors[9].address = OPT4003_I2C_ADDR_1;
//    light_sensors[9].sda_port = OPT4003_I2C_SDA_2_PORT;
//    light_sensors[9].sda_pin = OPT4003_I2C_SDA_2_PIN;
//    light_sensors[9].scl_port = OPT4003_I2C_SCL_2_PORT;
//    light_sensors[9].scl_pin = OPT4003_I2C_SCL_2_PIN;
//    OPT4003_Init(&light_sensors[9]);
//
//    light_sensors[10].address = OPT4003_I2C_ADDR_1;
//    light_sensors[10].sda_port = OPT4003_I2C_SDA_4_PORT;
//    light_sensors[10].sda_pin = OPT4003_I2C_SDA_4_PIN;
//    light_sensors[10].scl_port = OPT4003_I2C_SCL_4_PORT;
//    light_sensors[10].scl_pin = OPT4003_I2C_SCL_4_PIN;
//    OPT4003_Init(&light_sensors[10]);
//
//    light_sensors[11].address = OPT4003_I2C_ADDR_3;
//    light_sensors[11].sda_port = OPT4003_I2C_SDA_2_PORT;
//    light_sensors[11].sda_pin = OPT4003_I2C_SDA_2_PIN;
//    light_sensors[11].scl_port = OPT4003_I2C_SCL_2_PORT;
//    light_sensors[11].scl_pin = OPT4003_I2C_SCL_2_PIN;
//    OPT4003_Init(&light_sensors[11]);
//
//    light_sensors[12].address = OPT4003_I2C_ADDR_4;
//    light_sensors[12].sda_port = OPT4003_I2C_SDA_2_PORT;
//    light_sensors[12].sda_pin = OPT4003_I2C_SDA_2_PIN;
//    light_sensors[12].scl_port = OPT4003_I2C_SCL_2_PORT;
//    light_sensors[12].scl_pin = OPT4003_I2C_SCL_2_PIN;
//    OPT4003_Init(&light_sensors[12]);
//
//    light_sensors[13].address = OPT4003_I2C_ADDR_3;
//    light_sensors[13].sda_port = OPT4003_I2C_SDA_4_PORT;
//    light_sensors[13].sda_pin = OPT4003_I2C_SDA_4_PIN;
//    light_sensors[13].scl_port = OPT4003_I2C_SCL_4_PORT;
//    light_sensors[13].scl_pin = OPT4003_I2C_SCL_4_PIN;
//    OPT4003_Init(&light_sensors[13]);
}

void Exp_InstrumentLEDsOn(Exp_InstrumentWavelength wavelength) {
    wavelength_state[wavelength] = true;
    MPQ3326_TurnLEDsOn(&wavelength_descriptors[wavelength]);
}

void Exp_InstrumentLEDsOff(Exp_InstrumentWavelength wavelength) {
    wavelength_state[wavelength] = false;
    MPQ3326_TurnLEDsOff(&wavelength_descriptors[wavelength]);
}

void Exp_InstrumetToggleLEDs(Exp_InstrumentWavelength wavelength) {
    if(wavelength_state[wavelength]) {
        MPQ3326_TurnLEDsOff(&wavelength_descriptors[wavelength]);
    } else {
        MPQ3326_TurnLEDsOn(&wavelength_descriptors[wavelength]);
    }

    wavelength_state[wavelength] = !wavelength_state[wavelength];
}

void Exp_InstrumentSetBrightness(Exp_InstrumentWavelength wavelength, uint8_t brightness) {
    MPQ3326_SetBrightness(&wavelength_descriptors[wavelength], brightness);
}

void Exp_InstrumentRead(uint32_t buffer[EXP_INSTRUMENT_SENSOR_COUNT]) {
    int i;
    for(i = 0; i < EXP_INSTRUMENT_SENSOR_COUNT; i ++) {
        OPT4003_Read(&light_sensors[i], &buffer[i]);
    }
}
