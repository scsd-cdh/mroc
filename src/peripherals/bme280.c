/*
 * bme280.c
 *
 *  Created on: Feb. 6, 2024
 *      Author: Ruben
 */

#include <src/drivers/drivers.h>
#include <src/peripherals/bme280.h>

#define BUFFER_LENGTH 32
#define START_ADDR 0xF7
#define DATA_LENGTH 8

static uint8_t dataTransferred = 0;

// Circular buffer
static uint16_t bufferHead = 0;
static uint16_t bufferTail = 0;
static uint16_t bufferLen = 0;
static uint8_t buffer[BUFFER_LENGTH];

static uint8_t port;
static uint16_t pin;

void BME280_Init(BME280_Descriptor *descriptor) {
    // Set chip select
    GPIO_setAsOutputPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );

    GPIO_setOutputHighOnPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );

    port = descriptor->cs_port;
    pin  = descriptor->cs_pin;

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

    bufferHead = 0;
    bufferTail = 0;
    bufferLen = 0;

    GPIO_setOutputLowOnPin(
            descriptor->cs_port,
            descriptor->cs_pin
        );
    EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, 0x60);
    EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, 0xB6);
    GPIO_setOutputHighOnPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );
    __delay_cycles(100);

    GPIO_setOutputLowOnPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );
    EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, 0x74);
    EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, 0x27);
    GPIO_setOutputHighOnPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );
    __delay_cycles(100);

    GPIO_setOutputLowOnPin(
        descriptor->cs_port,
        descriptor->cs_pin
    );
    EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, START_ADDR);
}

void BME280_Read(ExperimentMonitor *data) {
    if (bufferLen < 8)
        return;

    data->ambient_pressure = ((int32_t)buffer[bufferHead] << 12) | ((int32_t)buffer[bufferHead+1] << 4) | ((buffer[bufferHead+2] >> 4) & 0x0F);
    data->ambient_temperature = ((int32_t)buffer[bufferHead+3] << 12) | ((int32_t)buffer[bufferHead+4] << 4) | ((buffer[bufferHead+5] >> 4) & 0x0F);
    data->ambient_humidity = ((int32_t)buffer[bufferHead+6] << 8) | (int32_t)buffer[bufferHead+7];

    bufferLen -= 8;
    bufferHead = (bufferHead + 8) % BUFFER_LENGTH;
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
            if(EUSCI_A_SPI_getInterruptStatus(EUSCI_A0_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT)) {
                buffer[bufferTail] = EUSCI_A_SPI_receiveData(EUSCI_A0_BASE);
                bufferTail = (bufferTail+ 1) % BUFFER_LENGTH;
                bufferLen ++;

                EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, START_ADDR);
                dataTransferred ++;

                if (dataTransferred == DATA_LENGTH) {
                    GPIO_setOutputHighOnPin(
                        port,
                        pin
                    );

                    dataTransferred = 0;
                }
            }
            break;
        default:
            break;
    }
}
