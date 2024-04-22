/******************************************************************************

    File Name: config.h
    Description: Contains all configuration defines for the project.

    Author: Ruben Sanchez
    Date: January 28th, 2024
    Version: 1

******************************************************************************/

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// Firmware Version
#define FIRMWARE_VERSION        1           // Maximum version is 31

// Experiment Thresholds
#define MIN_VIABLE_EXP_TEMP     5           // Celsius
#define MAX_VIABLE_EXP_TEMP     40          // Celsius
#define MIN_EXP_TEMP            20          // Celsius
#define MAX_EXP_TEMP            37          // Celsius
#define MIX_PUMP_DURATION       20         // Seconds
#define WELL_COUNT              14          // Units

// External I2C Buses
#define MAIN_I2C_SDA            GPIO_PIN6
#define MAIN_I2C_SCL            GPIO_PIN7
#define MAIN_I2C_PORT           GPIO_PORT_P1
#define MAIN_SLAVE_ADDR         0x48

#define REDUNDANT_I2C_SDA       GPIO_PIN1
#define REDUNDANT_I2C_SCL       GPIO_PIN1
#define REDUNDANT_I2C_SDA_PORT  GPIO_PORT_P3
#define REDUNDANT_I2C_SCL_PORT  GPIO_PORT_P4
#define REDUNDANT_SLAVE_ADDR    0x48

// Bipump Pinout
#define BIPUMP_Q2_PORT          GPIO_PORT_P9
#define BIPUMP_Q2_PIN           GPIO_PIN2
#define BIPUMP_Q1_PORT          GPIO_PORT_P9
#define BIPUMP_Q1_PIN           GPIO_PIN3
#define BIPUMP_Q6_PORT          GPIO_PORT_P9
#define BIPUMP_Q6_PIN           GPIO_PIN4
#define BIPUMP_Q5_PORT          GPIO_PORT_P9
#define BIPUMP_Q5_PIN           GPIO_PIN5

// Pump Pinout
#define PUMP_PORT               GPIO_PORT_P3
#define PUMP_PIN                GPIO_PIN3

// BME280 Pinout
#define BME_SDO_PORT            GPIO_PORT_P4
#define BME_SDO_PIN             GPIO_PIN3
#define BME_CS_PORT             GPIO_PORT_P1
#define BME_CS_PIN              GPIO_PIN4
#define BME_SCK_PORT            GPIO_PORT_P1
#define BME_SCK_PIN             GPIO_PIN5
#define BME_SDI_PORT            GPIO_PORT_P2
#define BME_SDI_PIN             GPIO_PIN0

// LMT01 Pinout
#define LMT01_PORT              GPIO_PORT_P2
#define LMT01_PIN               GPIO_PIN7

// Valve Pinout
#define VALVE_PORT              GPIO_PORT_P2
#define VALVE_PIN               GPIO_PIN1

// Heater Pinout
#define HEATER_PORT             GPIO_PORT_P5
#define HEATER_PIN              GPIO_PIN0

// MPQ3326 Pinout
#define MPQ3326_W570_ADDR       0x32
#define MPQ3326_W630_ADDR       0x36
#define MPQ3326_W470_ADDR       0x33
#define MPQ3326_W850_ADDR       0x34
#define MPQ3326_I2C_SDA_PxOUT   P3OUT
#define MPQ3326_I2C_SDA_PxIN    P3IN
#define MPQ3326_I2C_SDA_PxDIR   P3DIR
#define MPQ3326_I2C_SDA_PIN     GPIO_PIN0
#define MPQ3326_I2C_SCL_PxOUT   P5OUT
#define MPQ3326_I2C_SCL_PxIN    P5IN
#define MPQ3326_I2C_SCL_PxDIR   P5DIR
#define MPQ3326_I2C_SCL_PIN     GPIO_PIN3
#define MPQ3326_ENABLE_PORT     GPIO_PORT_P5
#define MPQ3326_ENABLE_PIN      GPIO_PIN1

// OPT4003 Pinout
#define OPT4003_I2C_ADDR_1      0x44
#define OPT4003_I2C_ADDR_2      0x45
#define OPT4003_I2C_ADDR_3      0x46
#define OPT4003_I2C_ADDR_4      0x47

#define OPT4003_I2C_SDA_1_PxOUT P2OUT
#define OPT4003_I2C_SDA_1_PxIN  P2IN
#define OPT4003_I2C_SDA_1_PxDIR P2DIR
#define OPT4003_I2C_SDA_1_PIN   GPIO_PIN2
#define OPT4003_I2C_SCL_1_PxOUT P2OUT
#define OPT4003_I2C_SCL_1_PxIN  P2IN
#define OPT4003_I2C_SCL_1_PxDIR P2DIR
#define OPT4003_I2C_SCL_1_PIN   GPIO_PIN3

#define OPT4003_I2C_SDA_2_PxOUT P1OUT
#define OPT4003_I2C_SDA_2_PxIN  P1IN
#define OPT4003_I2C_SDA_2_PxDIR P1DIR
#define OPT4003_I2C_SDA_2_PIN   GPIO_PIN1
#define OPT4003_I2C_SCL_2_PxOUT P1OUT
#define OPT4003_I2C_SCL_2_PxIN  P1IN
#define OPT4003_I2C_SCL_2_PxDIR P1DIR
#define OPT4003_I2C_SCL_2_PIN   GPIO_PIN0

#define OPT4003_I2C_SDA_3_PxOUT P9OUT
#define OPT4003_I2C_SDA_3_PxIN  P9IN
#define OPT4003_I2C_SDA_3_PxDIR P9DIR
#define OPT4003_I2C_SDA_3_PIN   GPIO_PIN7
#define OPT4003_I2C_SCL_3_PxOUT P9OUT
#define OPT4003_I2C_SCL_3_PxIN  P9IN
#define OPT4003_I2C_SCL_3_PxDIR P9DIR
#define OPT4003_I2C_SCL_3_PIN   GPIO_PIN6

#define OPT4003_I2C_SDA_4_PxOUT P3OUT
#define OPT4003_I2C_SDA_4_PxIN  P3IN
#define OPT4003_I2C_SDA_4_PxDIR P3DIR
#define OPT4003_I2C_SDA_4_PIN   GPIO_PIN6
#define OPT4003_I2C_SCL_4_PxOUT P3OUT
#define OPT4003_I2C_SCL_4_PxIN  P3IN
#define OPT4003_I2C_SCL_4_PxDIR P3DIR
#define OPT4003_I2C_SCL_4_PIN   GPIO_PIN5

#endif /* SRC_CONFIG_H_ */
