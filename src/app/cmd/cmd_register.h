/*
 * cmd_definition.h
 *
 *  Created on: Feb. 2, 2024
 *      Author: Ruben
 */

#ifndef CMD_CMD_DEFINITION_H_
#define CMD_CMD_DEFINITION_H_

#include <src/config.h>
#include <stdint.h>

void Cmd_RequestTelemetryFrame(uint8_t tlm_request);
uint8_t Cmd_ReadRegister();

void Cmd_SetSystemStatus(uint8_t state, uint32_t uptime_seconds);
void Cmd_SetExperimentStatusRegister(uint8_t last_state, uint8_t progress, uint32_t uptime);
void Cmd_SetHardwareHealthStatusRegister();
void Cmd_SetEnvironmentInformationRegister(uint16_t well_temperature, uint16_t ambient_temperature, uint16_t ambient_pressure, uint16_t ambient_humidity);
void Cmd_SetPhotosensorResults();
void Cmd_SetTelecommandAcknowledge(uint8_t tc_id, uint8_t tc_result);

typedef struct
{
    uint8_t firmware_version_and_state;
    uint32_t uptime_seconds;
} __attribute__((packed)) Cmd_SystemStatusRegister;

typedef struct
{
    uint8_t last_succesfull_state_and_progress;
    uint32_t uptime_seconds;
} __attribute__((packed)) Cmd_ExperimentStatusRegister;

typedef struct
{
    uint8_t leds_status[7];
    uint8_t other_devices;
} __attribute__((packed)) Cmd_HardwareHealthStatusRegister;

typedef struct
{
    uint16_t well_temperature;
    uint16_t ambient_temperature;
    uint16_t ambient_pressure;
    uint16_t ambient_humidity;
} __attribute__((packed)) Cmd_EnvironmentInformationRegister;

typedef struct {
    uint32_t results[WELL_COUNT];
}__attribute__((packed)) Cmd_PhotoSensorResultsRegister;

typedef struct
{
    uint8_t telecommand_id;
    uint8_t telecommand_result;
} __attribute__((packed)) Cmd_TelecommandAcknowledgeRegister;

#endif /* CMD_CMD_DEFINITION_H_ */
