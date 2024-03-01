/*
 * heater.c
 *
 *  Created on: Feb. 25, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_HEATER_C_
#define SRC_PERIPHERALS_HEATER_C_

#include "heater.h"
#include <src/drivers/drivers.h>

#define HEATER_PWM_TA_CTL TASSEL__SMCLK + MC__UP + TACLR
#define HEATER_PWM_TA_CCTL OUTMOD_7 // Reset/Set output mode for TA1.1
#define HEATER_PWM_TA_CCR0 1000 - 1
#define HEATER_PWM_TA_CCR1 500

void Heater_Init(Heater_Descriptor *descriptor) {
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        descriptor->port,
        descriptor->pin,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    TA1CTL = HEATER_PWM_TA_CTL;
    TA1CCTL1 = HEATER_PWM_TA_CCTL;
    TA1CCR0 = HEATER_PWM_TA_CCR0;
    TA1CCR1 = HEATER_PWM_TA_CCR1;
}

void Heater_Write(Heater_Descriptor *descriptor, uint8_t value) {
    if(value > 100) value = 100;
    TA1CCR1 = (value / 100) * TA1CCR0;
}

void Heater_Off(Heater_Descriptor *descriptor) {
    TA1CCR1 = 0;
}


#endif /* SRC_PERIPHERALS_HEATER_C_ */
