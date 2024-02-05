/*
 * cmd_register.c
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#include "cmd_register.h"
#include "cmd_list.h"
#include <src/config.h>

static Cmd_SystemStatusRegister systemStatusRegister;
static Cmd_ExperimentStatusRegister experimentStatusRegister;
static Cmd_HardwareHealthStatusRegister hardwareHealthStatusRegister;
static Cmd_EnvironmentInformationRegister environmentInformationRegister;
static Cmd_PhotoSensorResultsRegister photoSensorResultsRegister;
static Cmd_TelecommandAcknowledgeRegister telecommandAcknowledgeRegister;

static uint8_t* currentRegisterBuffer;
static uint8_t  currentRegisterBufferIdx;
static uint8_t  currentRegisterBufferLength;

void Cmd_RequestTelemetryFrame(uint8_t tlm_request) {
    currentRegisterBufferIdx = 0;
    switch(tlm_request) {
    case CMD_SYSTEM_STATUS:
        currentRegisterBuffer = (uint8_t*)&systemStatusRegister;
        currentRegisterBufferLength = sizeof(Cmd_SystemStatusRegister);
        break;
    case CMD_EXPERIMENT_STATUS:
        currentRegisterBuffer = (uint8_t*)&experimentStatusRegister;
        currentRegisterBufferLength = sizeof(Cmd_ExperimentStatusRegister);
        break;
    case CMD_HARDWARE_HEALTH_STATUS:
        currentRegisterBuffer = (uint8_t*)&hardwareHealthStatusRegister;
        currentRegisterBufferLength = sizeof(Cmd_HardwareHealthStatusRegister);
        break;
    case CMD_ENVIRONMENT_INFORMATION:
        currentRegisterBuffer = (uint8_t*)&environmentInformationRegister;
        currentRegisterBufferLength = sizeof(Cmd_EnvironmentInformationRegister);
        break;
    case CMD_PHOTOSENSOR_RESULTS:
        currentRegisterBuffer = (uint8_t*)&photoSensorResultsRegister;
        currentRegisterBufferLength = sizeof(Cmd_PhotoSensorResultsRegister);
        break;
    case CMD_TELECOMMAND_ACKNOWLEDGE:
        currentRegisterBuffer = (uint8_t*)&telecommandAcknowledgeRegister;
        currentRegisterBufferLength = sizeof(Cmd_TelecommandAcknowledgeRegister);
        break;
    default:
        currentRegisterBufferLength = 0;
        break;
    }
}

uint8_t Cmd_ReadRegister() {
    if (currentRegisterBufferIdx < currentRegisterBufferLength) {
        uint8_t data = currentRegisterBuffer[currentRegisterBufferIdx];
        currentRegisterBufferIdx++;
        return data;
    } else {
        return 0xFF;
    }
}

void Cmd_SetSystemStatus(uint8_t state, uint32_t uptime) {
    systemStatusRegister.firmware_version_and_state = (FIRMWARE_VERSION << 3) | state;
    systemStatusRegister.uptime_seconds = uptime;
}

void Cmd_SetExperimentStatusRegister(uint8_t last_state, uint8_t result, uint32_t uptime) {
    experimentStatusRegister.last_succesfull_state_and_progress = (last_state << 3) | result;
    experimentStatusRegister.uptime_seconds = uptime;
}

void Cmd_SetHardwareHealthStatusRegister() {
    hardwareHealthStatusRegister.other_devices = 255;
}

void Cmd_SetEnvironmentInformationRegister(uint16_t well_temperature, uint16_t ambient_temperature, uint16_t ambient_pressure, uint16_t ambient_humidity){
    environmentInformationRegister.well_temperature = well_temperature;
    environmentInformationRegister.ambient_temperature = ambient_temperature;
    environmentInformationRegister.ambient_pressure = ambient_pressure;
    environmentInformationRegister.ambient_humidity = ambient_humidity;
}

void Cmd_SetPhotosensorResults() {
    photoSensorResultsRegister.results = 150;
}

void Cmd_SetTelecommandAcknowledge(uint8_t tc_id, uint8_t tc_result) {
    telecommandAcknowledgeRegister.telecommand_id = tc_id;
    telecommandAcknowledgeRegister.telecommand_result = tc_result;
}
