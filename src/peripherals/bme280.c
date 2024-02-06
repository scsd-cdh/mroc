/*
 * bme280.c
 *
 *  Created on: Feb. 6, 2024
 *      Author: Ruben
 */

#include "bme280.h"
#include <src/drivers/drivers.h>

void BME280_Init(BME280_Descriptor *descriptor) {
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

    //Initialize Master
    EUSCI_A_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 500000;
    param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
    param.spiMode = EUSCI_A_SPI_3PIN;
    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &param);

    //Enable SPI module
    EUSCI_A_SPI_enable(EUSCI_A0_BASE);

    EUSCI_A_SPI_clearInterrupt(EUSCI_A0_BASE,
            EUSCI_A_SPI_RECEIVE_INTERRUPT);
    // Enable USCI_A0 RX interrupt
    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE,
        EUSCI_A_SPI_RECEIVE_INTERRUPT);
}

void BME280_Read(BME280_Descriptor *descriptor) {

}
