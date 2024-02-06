/*
 * humidity_temperature_pressure.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_BME280_H_
#define SRC_PERIPHERALS_BME280_H_

#include <stdint.h>

typedef struct {
    uint8_t miso_port;
    uint16_t miso_pin;
    uint8_t mosi_port;
    uint16_t mosi_pin;
    uint8_t sck_port;
    uint16_t sck_pin;
    uint8_t cs_port;
    uint16_t cs_pin;

    uint32_t pressure;
    uint32_t temperature;
    uint16_t humidity;
} BME280_Descriptor;

void BME280_Init(BME280_Descriptor *descriptor);
void BME280_Read(BME280_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_BME280_H_ */
