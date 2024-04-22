/*
 * bme280.c
 *
 *  Created on: Feb. 6, 2024
 *      Author: Ruben
 */

#include <src/drivers/drivers.h>
#include <src/peripherals/bme280.h>

typedef struct {
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;

    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;

    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t dig_H6;
} BME280_Calib_Data;

#define DUMMY   0xFF

#define SLAVE_CS_OUT    P1OUT
#define SLAVE_CS_DIR    P1DIR
#define SLAVE_CS_PIN    BIT4

#define RESET_REG_W         0x60
#define MEAS_START_REG      0xF7
#define CTRL_MEAS_REG_W     0x74
#define H_MEAS_REG_W        0x72
#define MAX_BUFFER_SIZE     120

uint8_t ResetRegVal [1] = {0xB6};
uint8_t CtrlMeasRegVal [1] = {0x27};
uint8_t HMeasRegVal[1] = {0x01};

typedef enum SPI_ModeEnum{
    IDLE_MODE,
    TX_REG_ADDRESS_MODE,
    RX_REG_ADDRESS_MODE,
    TX_DATA_MODE,
    RX_DATA_MODE,
    TIMEOUT_MODE
} SPI_Mode;
SPI_Mode MasterMode = IDLE_MODE;

uint8_t TransmitRegAddr = 0;

uint8_t ReceiveBuffer[MAX_BUFFER_SIZE] = {0};
uint8_t RXByteCtr = 0;
uint8_t ReceiveIndex = 0;
uint8_t TransmitBuffer[MAX_BUFFER_SIZE] = {0};
uint8_t TXByteCtr = 0;
uint8_t TransmitIndex = 0;

SPI_Mode SPI_Master_WriteReg(uint8_t reg_addr, uint8_t *reg_data, uint8_t count);
SPI_Mode SPI_Master_ReadReg(uint8_t reg_addr, uint8_t count);
void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count);
void SendUCA0Data(uint8_t val);

void CopyArray(uint8_t *source, uint8_t *dest, uint8_t count)
{
    uint8_t copyIndex = 0;
    for (copyIndex = 0; copyIndex < count; copyIndex++)
    {
        dest[copyIndex] = source[copyIndex];
    }
}

void SendUCA0Data(uint8_t val)
{
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = val;
}

SPI_Mode SPI_Master_WriteReg(uint8_t reg_addr, uint8_t *reg_data, uint8_t count)
{
    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = reg_addr;

    //Copy register data to TransmitBuffer
    CopyArray(reg_data, TransmitBuffer, count);

    TXByteCtr = count;
    RXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    SLAVE_CS_OUT &= ~(SLAVE_CS_PIN);
    SendUCA0Data(TransmitRegAddr);
    return MasterMode;
}

SPI_Mode SPI_Master_ReadReg(uint8_t reg_addr, uint8_t count)
{
    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = reg_addr;
    RXByteCtr = count;
    TXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    SLAVE_CS_OUT &= ~(SLAVE_CS_PIN);
    SendUCA0Data(TransmitRegAddr);
    return MasterMode;
}

void BME280_Init(BME280_Descriptor *descriptor) {
    // INIT SPI
    UCA0CTLW0 = UCSWRST;                                                    // **Put state machine in reset**
    UCA0CTLW0 |= UCCKPL + UCMSB + UCSYNC + UCMST + UCSSEL__SMCLK; // 3-pin, 8-bit SPI master in mode 3 with SMCLK
    UCA0BRW = 0x20;                                             // Setting baud rate control register (adjust as needed for your clock source and desired SPI clock rate)
    UCA0MCTLW = 0;                                              // Modulation control (not used in SPI mode, set to 0)
    UCA0CTLW0 &= ~UCSWRST;                                      // Initialize USCI state machine
    UCA0IE |= UCRXIE;

    // INIT GPIO
    P1SEL1 |= BIT5;
    P2SEL0 |= BIT0;
    P4SEL0 |= BIT3;

    SLAVE_CS_DIR |= SLAVE_CS_PIN;
    SLAVE_CS_OUT |= SLAVE_CS_PIN;

    // INT CLOCK TO 16 MHz
    FRCTL0 = FRCTLPW | NWAITS_1;

    // Clock System Setup
    CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
    CSCTL1 = DCORSEL | DCOFSEL_4;             // Set DCO to 16MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers

    CSCTL0_H = 0;

    SPI_Master_WriteReg(0x60, ResetRegVal, 1);
//    SPI_Master_WriteReg(0x72, HMeasRegVal, 1);
    SPI_Master_WriteReg(0x74, CtrlMeasRegVal, 1);
}

void BME280_Read(ExperimentMonitor *data) {
    if (ReceiveIndex < 118) {
        SPI_Master_ReadReg(0x88, 118);
        return;
    }

    int32_t var1, var2, v_x1_u32r;
    int32_t adc_P, adc_T, adc_H;
    int32_t p, t;
    int32_t t_fine;
    BME280_Calib_Data calData;

    // Convert byte data into correct calibration data
    calData.dig_T1 = (ReceiveBuffer[1] << 8) | ReceiveBuffer[0];
    calData.dig_T2 = (ReceiveBuffer[3] << 8) | ReceiveBuffer[2];
    calData.dig_T3 = (ReceiveBuffer[5] << 8) | ReceiveBuffer[4];
    calData.dig_P1 = (ReceiveBuffer[7] << 8) | ReceiveBuffer[6];
    calData.dig_P2 = (ReceiveBuffer[9] << 8) | ReceiveBuffer[8];
    calData.dig_P3 = (ReceiveBuffer[11] << 8) | ReceiveBuffer[10];
    calData.dig_P4 = (ReceiveBuffer[13] << 8) | ReceiveBuffer[12];
    calData.dig_P5 = (ReceiveBuffer[15] << 8) | ReceiveBuffer[14];
    calData.dig_P6 = (ReceiveBuffer[17] << 8) | ReceiveBuffer[16];
    calData.dig_P7 = (ReceiveBuffer[19] << 8) | ReceiveBuffer[18];
    calData.dig_P8 = (ReceiveBuffer[21] << 8) | ReceiveBuffer[20];
    calData.dig_P9 = (ReceiveBuffer[23] << 8) | ReceiveBuffer[22];
    calData.dig_H1 = ReceiveBuffer[25];
    calData.dig_H2 = (ReceiveBuffer[26 + 1] << 8) | ReceiveBuffer[26];
    calData.dig_H3 = ReceiveBuffer[26 + 2];
    calData.dig_H4 = (ReceiveBuffer[26 + 3] << 4) | (ReceiveBuffer[26 + 4] & 0x0F);
    calData.dig_H5 = (ReceiveBuffer[26 + 4] >> 4) | (ReceiveBuffer[26 + 5] << 4);
    calData.dig_H6 = (int8_t)ReceiveBuffer[26 + 6];

    uint16_t sensorDataIndex = 111;

    adc_P = ((int32_t)ReceiveBuffer[sensorDataIndex + 0] << 12) | ((int32_t)ReceiveBuffer[sensorDataIndex + 1] << 4) | ((int32_t)ReceiveBuffer[sensorDataIndex + 2] >> 4);
    adc_T = ((int32_t)ReceiveBuffer[sensorDataIndex + 3] << 12) | ((int32_t)ReceiveBuffer[sensorDataIndex + 4] << 4) | ((int32_t)ReceiveBuffer[sensorDataIndex + 5] >> 4);
    adc_H = ((int32_t)ReceiveBuffer[sensorDataIndex + 6] << 8) | (int32_t)ReceiveBuffer[sensorDataIndex + 7];

    // TEMPERATURE
    var1 = ((((adc_T >> 3) - ((int32_t)calData.dig_T1 << 1))) * ((int32_t)calData.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)calData.dig_T1)) * ((adc_T >> 4) - ((int32_t)calData.dig_T1))) >> 12) *
            ((int32_t)calData.dig_T3)) >> 14;
    t_fine = var1 + var2;
    t = (t_fine * 5 + 128) >> 8;
    data->ambient_temperature = t;

    // PRESSURE
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)calData.dig_P6;
    var2 = var2 + ((var1 * (int64_t)calData.dig_P5) << 17);
    var2 = var2 + (((int64_t)calData.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)calData.dig_P3) >> 8) + ((var1 * (int64_t)calData.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)calData.dig_P1) >> 33;

    if (var1 == 0) {
        p = 0;
    } else {
        p = 1048576 - adc_P;
        p = (((p << 31) - var2) * 3125) / var1;
        var1 = (((int64_t)calData.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
        var2 = (((int64_t)calData.dig_P8) * p) >> 19;

        p = ((p + var1 + var2) >> 8) + (((int64_t)calData.dig_P7) << 4);
    }
    data->ambient_pressure = (uint32_t)p;

    // HUMIDITY
    v_x1_u32r = (t_fine - ((int32_t)76800));
    v_x1_u32r = (((((adc_H << 14) - (((int32_t)calData.dig_H4) << 20) - (((int32_t)calData.dig_H5) * v_x1_u32r)) +
                ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)calData.dig_H6)) >> 10) *
                (((v_x1_u32r * ((int32_t)calData.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
                ((int32_t)calData.dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)calData.dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

    data->ambient_humidity = (uint32_t)(v_x1_u32r >> 12);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    uint8_t uca0_rx_val = 0;
    switch(__even_in_range(UCA0IV, USCI_SPI_UCTXIFG))
    {
        case USCI_NONE: break;
        case USCI_SPI_UCRXIFG:
            uca0_rx_val = UCA0RXBUF;
            UCA0IFG &= ~UCRXIFG;
            switch (MasterMode)
            {
                case TX_REG_ADDRESS_MODE:
                    if (RXByteCtr)
                    {
                        MasterMode = RX_DATA_MODE;
                        __delay_cycles(2000000);
                        SendUCA0Data(DUMMY);
                    }
                    else
                    {
                        MasterMode = TX_DATA_MODE;
                        SendUCA0Data(TransmitBuffer[TransmitIndex++]);
                        TXByteCtr--;
                    }
                    break;

                case TX_DATA_MODE:
                    if (TXByteCtr)
                    {
                      SendUCA0Data(TransmitBuffer[TransmitIndex++]);
                      TXByteCtr--;
                    }
                    else
                    {
                      MasterMode = IDLE_MODE;
                      SLAVE_CS_OUT |= SLAVE_CS_PIN;
                    }
                    break;

                case RX_DATA_MODE:
                    if (RXByteCtr)
                    {
                        ReceiveBuffer[ReceiveIndex++] = uca0_rx_val;
                        RXByteCtr--;
                    }
                    if (RXByteCtr == 0)
                    {
                        MasterMode = IDLE_MODE;
                        SLAVE_CS_OUT |= SLAVE_CS_PIN;
                    }
                    else
                    {
                        SendUCA0Data(DUMMY);
                    }
                    break;

                default:
                    __no_operation();
                    break;
            }
            __delay_cycles(1000);
            break;
        case USCI_SPI_UCTXIFG:
            break;
        default: break;
    }
}
