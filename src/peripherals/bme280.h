/*
 * humidity_temperature_pressure.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_BME280_H_
#define SRC_PERIPHERALS_BME280_H_

#include <stdint.h>
#include <extern/bme280.h>

typedef struct bme280_data BME280_Data;
typedef struct bme280_dev BME280_Device;
typedef struct bme280_settings BME280_Settings;

typedef struct {
    uint8_t miso_port;
    uint16_t miso_pin;
    uint8_t mosi_port;
    uint16_t mosi_pin;
    uint8_t sck_port;
    uint16_t sck_pin;
    uint8_t cs_port;
    uint16_t cs_pin;
} BME280_Descriptor;

int8_t BME280_Init(BME280_Descriptor *descriptor);
int8_t BME280_Read(BME280_Descriptor *descriptor, BME280_Data *data);


#endif /* SRC_PERIPHERALS_BME280_H_ */
