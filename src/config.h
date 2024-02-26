/*
 * config.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// Firmware Version
#define FIRMWARE_VERSION        1 // Maximum version is 31

// Experiment Thresholds
#define MIN_VIABLE_EXP_TEMP     5.0  // Celsius
#define MAX_VIABLE_EXP_TEMP     40.0 // Celsius
#define MIN_EXP_TEMP            20.0 // Celsius
#define MAX_EXP_TEMP            37.0 // Celsius
#define MIX_PUMP_DURATION       20.0 // Seconds

// External I2C Buses
#define MAIN_I2C_SDA            GPIO_PIN6
#define MAIN_I2C_SCL            GPIO_PIN7
#define MAIN_I2C_PORT           GPIO_PORT_P1
#define MAIN_SLAVE_ADDR         0x48

#define REDUNDANT_I2C_SDA       GPIO_PIN1
#define REDUNDANT_I2C_SCL       GPIO_PIN2
#define REDUNDANT_I2C_PORT      GPIO_PORT_P3
#define REDUNDANT_SLAVE_ADDR    0x48

// Bipump Pinout
#define BIPUMP_FORWARD_N_PORT   GPIO_PORT_P2
#define BIPUMP_FORWARD_N_PIN    GPIO_PIN1
#define BIPUMP_FORWARD_P_PORT   GPIO_PORT_P2
#define BIPUMP_FORWARD_P_PIN    GPIO_PIN2
#define BIPUMP_BACKWARD_N_PORT  GPIO_PORT_P2
#define BIPUMP_BACKWARD_N_PIN   GPIO_PIN3
#define BIPUMP_BACKWARD_P_PORT  GPIO_PORT_P2
#define BIPUMP_BACKWARD_P_PIN   GPIO_PIN4

// Pump Pinout
#define PUMP_PORT               GPIO_PORT_P3
#define PUMP_PIN                GPIO_PIN7

// BME280 Pinout

// LMT01 Pinout
#define LMT01_PORT              GPIO_PORT_P5
#define LMT01_PIN               GPIO_PIN0

// MPQ3326 Pinout
#define MPQ3326_W570_ADDR       0x36
#define MPQ3326_W630_ADDR       0x37
#define MPQ3326_W470_ADDR       0x38
#define MPQ3326_W850_ADDR       0x39
#define MPQ3326_I2C_SDA_PORT    GPIO_PORT_P3
#define MPQ3326_I2C_SDA_PIN     GPIO_PIN0
#define MPQ3326_I2C_SCL_PORT    GPIO_PORT_P5
#define MPQ3326_I2C_SCL_PIN     GPIO_PIN3

// Valve Pinout
#define VALVE_PORT              GPIO_PORT_P3
#define VALVE_PIN               GPIO_PIN6

// Heater Pinout
#define HEATER_PORT             GPIO_PORT_P9
#define HEATER_PIN              GPIO_PIN6

#endif /* SRC_CONFIG_H_ */
