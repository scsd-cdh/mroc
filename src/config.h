/*
 * config.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// Firmware Version
#define FIRMWARE_VERSION        0

// Ring Buffer
#define RING_BUFFER_SIZE        32

// External I2C Buses
#define MAIN_I2C_SDA            GPIO_PIN6
#define MAIN_I2C_SCL            GPIO_PIN5
#define MAIN_I2C_PORT           GPIO_PORT_P3
#define MAIN_SLAVE_ADDR         0x48

#define REDUNDANT_I2C_SDA       BIT1
#define REDUNDANT_I2C_SCL       BIT2
#define REDUNDANT_I2C_PORT      P3SEL1
#define REDUNDANT_SLAVE_ADDR    0x48

#endif /* SRC_CONFIG_H_ */
