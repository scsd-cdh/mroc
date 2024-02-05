/*
 * spectrophotometry.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_SPECTROPHOTOMETER_H_
#define SRC_PERIPHERALS_SPECTROPHOTOMETER_H_

#include <stdint.h>
#include <stdbool.h>

#define W470NM 0
#define W570NM 1
#define W630NM 2
#define W850NM 3

typedef struct
{
    // LED
    bool led_on;
    uint16_t led_brightness;
    uint8_t led_wavelength;
    uint8_t led_i2c_port;
    uint16_t led_i2c_sda;
    uint16_t led_i2c_scl;
    uint8_t led_slave_addr;

    uint16_t sensor_measurement;
    uint8_t sensor_i2c_port;
    uint16_t sensor_i2c_sda;
    uint16_t sensor_i2c_scl;
    uint8_t sensor_slave_addr;
} Spec_Descriptor;

void Spec_Init(Spec_Descriptor *descriptor);
void Spec_Capture(Spec_Descriptor *descriptor);
void Spec_SetBrightness(Spec_Descriptor *descriptor);
void Spec_SetLedOn(Spec_Descriptor *descriptor);
void Spec_SetLedOff(Spec_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_SPECTROPHOTOMETER_H_ */
