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
    uint16_t miso;
    uint16_t mosi;
    uint16_t sck;
    uint16_t cs;

    uint32_t pressure;
    uint32_t temperature;
    uint16_t humidity;
} BME280_Descriptor;

void BME280_Init(BME280_Descriptor *descriptor);
void BME280_Read(BME280_Descriptor *descriptor);

#endif /* SRC_PERIPHERALS_BME280_H_ */
