/*
 * swi2c.c
 *
 *  Created on: Feb. 21, 2024
 *      Author: Ruben
 */

#include "swi2c.h"
#include <src/drivers/drivers.h>

void SWI2C_SendStart(SWI2C_Descriptor *descriptor);

void SWI2C_Init(SWI2C_Descriptor *descriptor) {
    // Initialize scl pin
    GPIO_setAsOutputPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );
    GPIO_setOutputHighOnPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );

    // Initialize sda pin
    GPIO_setAsOutputPin(
        descriptor->sda_port,
        descriptor->sda_pin
    );
    GPIO_setOutputHighOnPin(
        descriptor->sda_port,
        descriptor->sda_pin
    );

    TB0CCR0 = SWI2C_TIMER_PERIOD;
}

int32_t SWI2C_Read(SWI2C_Descriptor *descriptor, uint8_t *buffer, uint16_t len) {
    uint_fast8_t bits, temp;
    uint16_t ii = 0;

    // Start Timer
    TB0CTL = TBSSEL_2 + MC_1 + TBCLR;

    // Send Start
    SWI2C_SendStart(descriptor);

    // Send Address with Read Instruction
    //         7 BIT ADDRESS          |    READ
    temp = (descriptor->address << 1) | 0b00000001;
    bits = 8;

    // Loop to send bit by bit of the address
    do
    {
        if (temp & 0b10000000) {
            GPIO_setOutputHighOnPin(
                descriptor->sda_port,
                descriptor->sda_pin
            );
        } else {
            GPIO_setOutputLowOnPin(
                descriptor->sda_port,
                descriptor->sda_pin
            );
        }

        GPIO_setOutputHighOnPin(
            descriptor->scl_port,
            descriptor->scl_pin
        );
        TIMER_ITERATION();

        temp = (temp << 1);
        bits = (bits - 1);
        GPIO_setOutputLowOnPin(
            descriptor->scl_port,
            descriptor->scl_pin
        );
        TIMER_ITERATION();

    }
    while (bits > 0);

    // Check for NAK
    GPIO_setAsInputPin(descriptor->sda_port, descriptor->sda_pin);
    TIMER_ITERATION();
    if (GPIO_getInputPinValue(descriptor->sda_port, descriptor->sda_pin) == GPIO_INPUT_PIN_HIGH)
    {
        goto I2CReadTransactionCleanUp;
    }
    GPIO_setAsOutputPin(descriptor->sda_port, descriptor->sda_pin);

    // Read data
    for (ii = 0; ii < len; ii++)
    {
        temp = 0;
        bits = 8;

        GPIO_setOutputLowOnPin(
            descriptor->scl_port,
            descriptor->scl_pin
        );
        TIMER_ITERATION();
        GPIO_setOutputHighOnPin(
            descriptor->sda_port,
            descriptor->sda_pin
        );

        // Loop and read bit by bit
        GPIO_setAsInputPin(descriptor->sda_port, descriptor->sda_pin);
        do
        {
            temp = (temp << 1);
            GPIO_setOutputHighOnPin(
                descriptor->scl_port,
                descriptor->scl_pin
            );
            TIMER_ITERATION();

            if (GPIO_getInputPinValue(descriptor->sda_port, descriptor->sda_pin) == GPIO_INPUT_PIN_HIGH)
            {
                temp += 1;
            }

            bits = (bits - 1);
            GPIO_setOutputLowOnPin(
                descriptor->scl_port,
                descriptor->scl_pin
            );
            TIMER_ITERATION();
        }
        while (bits > 0);

        buffer[ii] = temp;

        GPIO_setAsOutputPin(descriptor->sda_port, descriptor->sda_pin);
        if (ii == len - 1) {
            GPIO_setOutputHighOnPin(
                descriptor->sda_port,
                descriptor->sda_pin
            );
        } else {
            GPIO_setOutputLowOnPin(
                descriptor->sda_port,
                descriptor->sda_pin
            );
        }
        GPIO_setOutputHighOnPin(
            descriptor->scl_port,
            descriptor->scl_pin
        );

        GPIO_setAsInputPin(descriptor->scl_port, descriptor->scl_pin);
        while (GPIO_getInputPinValue(descriptor->scl_port, descriptor->scl_pin) != GPIO_INPUT_PIN_HIGH);
        GPIO_setAsOutputPin(descriptor->scl_port, descriptor->scl_pin);
        TIMER_ITERATION();
    }

    I2CReadTransactionCleanUp:

    // Send Stop
    GPIO_setOutputLowOnPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );
    GPIO_setOutputLowOnPin(
        descriptor->sda_port,
        descriptor->sda_pin
    );
    TIMER_ITERATION();
    GPIO_setOutputHighOnPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );
    __no_operation();
    GPIO_setOutputHighOnPin(
        descriptor->sda_port,
        descriptor->sda_pin
    );
    TIMER_ITERATION();

    // Stop The timer
    TB0CTL = MC_0;
    return ii;
}

int32_t SWI2C_Write(SWI2C_Descriptor *descriptor, uint8_t *buffer, uint16_t len) {
    uint_fast8_t bits, temp;
    uint16_t ii = 0;

    // Start the timer
    TB0CTL = TBSSEL_2 + MC_1 + TBCLR;

    // Send Start
    SWI2C_SendStart(descriptor);

    // Send Address with Write Instruction
    temp = (descriptor->address << 1);
    bits = 8;

    // Write Address with Instruction bit by bit
    do
    {
        if (temp & 0b10000000) {
            GPIO_setOutputHighOnPin(
                descriptor->sda_port,
                descriptor->sda_pin
            );
        } else {
            GPIO_setOutputLowOnPin(
                descriptor->sda_port,
                descriptor->sda_pin
            );
        }

        GPIO_setOutputHighOnPin(
            descriptor->scl_port,
            descriptor->scl_pin
        );
        TIMER_ITERATION();

        temp = (temp << 1);
        bits = (bits - 1);
        GPIO_setOutputLowOnPin(
            descriptor->scl_port,
            descriptor->scl_pin
        );
        TIMER_ITERATION();

    }
    while (bits > 0);

    // Detecting NAK
    GPIO_setAsInputPin(descriptor->scl_port, descriptor->scl_pin);
    GPIO_setAsInputPin(descriptor->sda_port, descriptor->sda_pin);
    while (GPIO_getInputPinValue(descriptor->scl_port, descriptor->scl_pin) != GPIO_INPUT_PIN_HIGH);

    TIMER_ITERATION();

    if (GPIO_getInputPinValue(descriptor->sda_port, descriptor->sda_pin) == GPIO_INPUT_PIN_HIGH)
    {
        goto I2CWriteTransactionCleanUp;
    }

    GPIO_setAsOutputPin(descriptor->scl_port, descriptor->scl_pin);
    GPIO_setAsOutputPin(descriptor->sda_port, descriptor->sda_pin);

    GPIO_setOutputLowOnPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );
    TIMER_ITERATION();

    // Send Buffer
    for (ii = 0; ii < len; ii++)
    {
        temp = buffer[ii];
        bits = 8;

        // Send bit by bit
        do
        {
            if (temp & 0b10000000) {
                GPIO_setOutputHighOnPin(
                    descriptor->sda_port,
                    descriptor->sda_pin
                );
            } else {
                GPIO_setOutputLowOnPin(
                    descriptor->sda_port,
                    descriptor->sda_pin
                );
            }

            GPIO_setOutputHighOnPin(
                descriptor->scl_port,
                descriptor->scl_pin
            );
            TIMER_ITERATION();

            temp = (temp << 1);
            bits = (bits - 1);
            GPIO_setOutputLowOnPin(
                descriptor->scl_port,
                descriptor->scl_pin
            );
            TIMER_ITERATION();

        }
        while (bits > 0);

        // Detecting NAK
        GPIO_setAsInputPin(descriptor->scl_port, descriptor->scl_pin);
        GPIO_setAsInputPin(descriptor->sda_port, descriptor->sda_pin);
        while (GPIO_getInputPinValue(descriptor->scl_port, descriptor->scl_pin) != GPIO_INPUT_PIN_HIGH);

        TIMER_ITERATION();

        if (GPIO_getInputPinValue(descriptor->sda_port, descriptor->sda_pin) == GPIO_INPUT_PIN_HIGH)
        {
            goto I2CWriteTransactionCleanUp;
        }

        GPIO_setAsOutputPin(descriptor->scl_port, descriptor->scl_pin);
        GPIO_setAsOutputPin(descriptor->sda_port, descriptor->sda_pin);

        GPIO_setOutputLowOnPin(
            descriptor->scl_port,
            descriptor->scl_pin
        );
        TIMER_ITERATION();
    }

    I2CWriteTransactionCleanUp:
    GPIO_setOutputLowOnPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );
    TIMER_ITERATION();
    GPIO_setOutputLowOnPin(
        descriptor->sda_port,
        descriptor->sda_pin
    );
    TIMER_ITERATION();
    GPIO_setOutputHighOnPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );
    __no_operation();
    GPIO_setOutputHighOnPin(
        descriptor->sda_port,
        descriptor->sda_pin
    );

    // Stop timer
    TB0CTL = MC_0;
    return ii;
}

void SWI2C_SendStart(SWI2C_Descriptor *descriptor) {
    GPIO_setOutputLowOnPin(
        descriptor->sda_port,
        descriptor->sda_pin
    );
    __no_operation();
    GPIO_setOutputLowOnPin(
        descriptor->scl_port,
        descriptor->scl_pin
    );
    TIMER_ITERATION();
}
