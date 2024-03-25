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
    param.spiMode = EUSCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW;
    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &param);
    EUSCI_A_SPI_enable(EUSCI_A0_BASE);
    EUSCI_A_SPI_clearInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);

    return 0;
}

int8_t BME280_Read(BME280_Descriptor *descriptor, BME280_Data *data) {
    return 0;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A0_VECTOR)))
#endif
void USCI_A0_ISR(void)
{
    switch(__even_in_range(UCA0IV, USCI_SPI_UCTXIFG))
    {
        case USCI_SPI_UCRXIFG:      // UCRXIFG
//            //USCI_A0 TX buffer ready?
//            while (!EUSCI_A_SPI_getInterruptStatus(EUSCI_A0_BASE,
//                EUSCI_A_SPI_TRANSMIT_INTERRUPT));
//
//            RXData = EUSCI_A_SPI_receiveData(EUSCI_A0_BASE);
//
//            //Send next value
//            EUSCI_A_SPI_transmitData(EUSCI_A0_BASE,
//                TXData
//                );
//
//            //Delay between transmissions for slave to process information
//            __delay_cycles(40);
            break;
        default:
            break;
    }
}
