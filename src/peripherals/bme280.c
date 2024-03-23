/*
 * bme280.c
 *
 *  Created on: Feb. 6, 2024
 *      Author: Ruben
 */

#include <src/drivers/drivers.h>
#include <src/peripherals/bme280.h>

#define SAMPLE_COUNT  50

static BME280_Device dev;
static BME280_Settings settings;
static uint32_t period;

int8_t BME280_Init(BME280_Descriptor *descriptor) {
    // Set chip select
    GPIO_setAsOutputPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );

    GPIO_setOutputLowOnPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );

    CS_setDCOFreq(CS_DCORSEL_0,CS_DCOFSEL_3);
    CS_initClockSignal(CS_SMCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);

    // Set clock pins
    GPIO_setAsPeripheralModuleFunctionInputPin(
        descriptor->sck_port,
        descriptor->sck_pin,
        GPIO_SECONDARY_MODULE_FUNCTION
    );

    // Set MISO and MOSI pins
    GPIO_setAsPeripheralModuleFunctionInputPin(
        descriptor->miso_port,
        descriptor->miso_pin,
        GPIO_SECONDARY_MODULE_FUNCTION
    );

    GPIO_setAsPeripheralModuleFunctionInputPin(
        descriptor->mosi_port,
        descriptor->mosi_pin,
        GPIO_SECONDARY_MODULE_FUNCTION
    );

    EUSCI_A_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 500000;
    param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    param.spiMode = EUSCI_A_SPI_3PIN;
    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &param);
    EUSCI_A_SPI_enable(EUSCI_A0_BASE);
    EUSCI_A_SPI_clearInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);

    return 0;
}

int8_t BME280_Read(BME280_Descriptor *descriptor, BME280_Data *data) {
    return 0;
}
