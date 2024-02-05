/*
 * cmd_list.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_CMD_CMD_LIST_H_
#define SRC_APP_CMD_CMD_LIST_H_

// Telecommands
#define CMD_NEXT_EXPERIMENT_PHASE   0x01
#define CMD_RUN_EXPERIMENT_PHASE    0x02
#define CMD_SET_LED_STATE           0x03
#define CMD_TEST_SYSTEM_HEALTH      0x04
#define CMD_SET_STATE_IDLE          0x05
#define CMD_RESET                   0x55
#define CMD_TC_MAX                  0x7F

// Telemetry Request
#define CMD_SYSTEM_STATUS           0x80
#define CMD_EXPERIMENT_STATUS       0x81
#define CMD_HARDWARE_HEALTH_STATUS  0x82
#define CMD_ENVIRONMENT_INFORMATION 0x83
#define CMD_PHOTOSENSOR_RESULTS     0x84
#define CMD_TELECOMMAND_ACKNOWLEDGE 0x85

#define CMD_UNDEFINED               0xFF

#endif /* SRC_APP_CMD_CMD_LIST_H_ */
