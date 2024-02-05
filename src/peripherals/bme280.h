/*
 * humidity_temperature_pressure.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_BME280_H_
#define SRC_PERIPHERALS_BME280_H_

typedef struct {
    uint16_t miso;
    uint16_t mosi;
    uint16_t sck;
    uint16_t cs;
} BME280_Descriptor;

#endif /* SRC_PERIPHERALS_BME280_H_ */
