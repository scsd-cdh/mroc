/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
#include "swi2c_master.h"

/* Static Functions */
static bool SWI2C_readData(uint8_t addr, uint8_t *inputArray,
                           uint_fast16_t size);
static bool SWI2C_writeData(uint8_t addr, uint8_t *outputArray,
                            uint_fast16_t size, bool sendStop);

void SWI2C_initI2C(void)
{

    /* Using the direction pin to control the output. When set as an input, the
     hardware pull-ups will take over and cause the pin to go high. When
     set as an output, the MSP430 will drive the lines low */
    SWI2C_PxOUT &= ~SWI2C_SDA;
    SWI2C_PxOUT &= ~SWI2C_SCL;

    SWI2C_SCL_HIGH;
    SWI2C_SDA_HIGH;

    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
                          // to activate previously configured port settings

    /* Timer is initialized to run off SMCLK(8MHz) with frequency 200KHz */
    TB0CCR0 = SWI2C_TIMER_PERIOD;
}

bool SWI2C_performI2CTransaction(SWI2C_I2CTransaction *i2cTransaction)
{
    if (i2cTransaction->numWriteBytes > 0)
    {
        /* Only skipping the stop if we have a repeated start to send */
        if (i2cTransaction->repeatedStart && i2cTransaction->numReadBytes > 0)
        {
            if (!SWI2C_writeData(i2cTransaction->address,
                                 i2cTransaction->writeBuffer,
                                 i2cTransaction->numWriteBytes, false))
            {
                return false;
            }
        }
        else
        {
            if (!SWI2C_writeData(i2cTransaction->address,
                                 i2cTransaction->writeBuffer,
                                 i2cTransaction->numWriteBytes, true))
            {
                return false;
            }
        }
    }

    /* Next doing the read */
    if (i2cTransaction->numReadBytes > 0)
    {
        if (!SWI2C_readData(i2cTransaction->address, i2cTransaction->readBuffer,
                            i2cTransaction->numReadBytes))
        {
            return false;
        }
    }

    return true;
}

static bool SWI2C_writeData(uint8_t addr, uint8_t *outputArray,
                            uint_fast16_t size, bool sendStop)
{
    uint_fast8_t bits, temp;
    uint16_t ii = 0;

    /* Starting the timer */
    TB0CTL = TBSSEL_2 + MC_1 + TBCLR;

    /* Sending the START */
    SWI2C_SDA_LOW;
    __no_operation();
    SWI2C_SCL_LOW;
    TIMER_ITERATION();

    /* Next doing the control byte */
    temp = (addr << 1);
    bits = 8;

    /* Loop until all bits of the address byte are sent out */
    do
    {
        /* Deciding if we want to send a high or low out of the line */
        if (temp & BIT7)
        {
            SWI2C_SDA_HIGH;
        }
        else
        {
            SWI2C_SDA_LOW;
        }

        /* Now that we set the SDA line, we have to send out a clock pulse */
        SWI2C_SCL_HIGH;
        TIMER_ITERATION();

        /* Incrementing to the next bit and waiting for the next clock cycle */
        temp = (temp << 1);
        bits = (bits - 1);

        SWI2C_SCL_LOW;
        TIMER_ITERATION();

    }
    while (bits > 0);

    /* Detecting if we have a NAK on the bus. If the slave device NAKed the
     control byte, it probably isn't there on the bus so we should send
     an I2C stop and return false */
    SWI2C_SDA_HIGH;
    SWI2C_SCL_HIGH;
    /*
     * Waiting for our clock line to go high if the slave is stretching
     */
    while (!(SWI2C_PxIN & SWI2C_SCL))
        ;

    TIMER_ITERATION();

    if (SWI2C_PxIN & SWI2C_SDA)
    {
        goto I2CWriteTransactionCleanUp;
    }

    /* Sending out another clock cycle */
    SWI2C_SCL_LOW;
    TIMER_ITERATION();

    /* Next, let us send out all bytes in the user buffer */
    for (ii = 0; ii < size; ii++)
    {
        temp = outputArray[ii];
        bits = 8;

        /* Loop until all bits of the current byte are sent out */
        do
        {
            /* Deciding if we want to send a high or low out of the line */
            if (temp & BIT7)
            {
                SWI2C_SDA_HIGH;
            }
            else
            {
                SWI2C_SDA_LOW;
            }

            /* Now that we set the SDA line, we send out a clock pulse */
            SWI2C_SCL_HIGH;
            TIMER_ITERATION();

            /* Incrementing to the next bit and waiting for next clock cycle */
            temp = (temp << 1);
            bits = (bits - 1);
            SWI2C_SCL_LOW;
            TIMER_ITERATION();

        }
        while (bits > 0);

        /* Detecting the NAK. We should break out of the send loop */
        SWI2C_SDA_HIGH;
        SWI2C_SCL_HIGH;
        /*
         * Waiting for our clock line to go high if the slave is stretching
         */
        while (!(SWI2C_PxIN & SWI2C_SCL))
            ;

        TIMER_ITERATION();

        if (SWI2C_PxIN & SWI2C_SDA)
        {
            goto I2CWriteTransactionCleanUp;
        }

        /* Sending out another clock cycle */
        SWI2C_SCL_LOW;
        TIMER_ITERATION();
    }

    I2CWriteTransactionCleanUp:
    /* If the user did not request to skip, we send out the stop bit */
    if ((sendStop && ii == size) || (ii != size))
    {
        SWI2C_SCL_LOW;
        TIMER_ITERATION();
        SWI2C_SDA_LOW;
        TIMER_ITERATION();
        SWI2C_SCL_HIGH;
        __no_operation();
        SWI2C_SDA_HIGH;
    }
    else
    {
        SWI2C_SCL_HIGH;
        SWI2C_SDA_HIGH;
    }

    /* Stop the timer */
    TB0CTL = MC_0;

    /* If all bytes were sent, return true- otherwise false. */
    if (ii == size)
        return true;
    else
        return false;
}

static bool SWI2C_readData(uint8_t addr, uint8_t *inputArray,
                           uint_fast16_t size)
{
    uint_fast8_t bits, temp;
    uint16_t ii = 0;

    /* Starting the timer */
    TB0CTL = TBSSEL_2 + MC_1 + TBCLR;

    /* Sending the START */
    SWI2C_SDA_LOW;
    __no_operation();
    SWI2C_SCL_LOW;
    TIMER_ITERATION();

    /* Next doing the control byte */
    temp = (addr << 1) | BIT0;
    bits = 8;

    /* Loop until all bits of the address byte are sent out */
    do
    {
        /* Deciding if we want to send a high or low out of the line */
        if (temp & BIT7)
        {
            SWI2C_SDA_HIGH;
        }
        else
        {
            SWI2C_SDA_LOW;
        }

        /* Now that we set the SDA line, we have to send out a clock pulse */
        SWI2C_SCL_HIGH;
        TIMER_ITERATION();

        /* Incrementing to the next bit and waiting for the next clock cycle */
        temp = (temp << 1);
        bits = (bits - 1);
        SWI2C_SCL_LOW;
        TIMER_ITERATION();

    }
    while (bits > 0);

    /* Detecting if we have a NAK on the bus. If the slave device NAKed the
     control byte, it probably isn't there on the bus so we should send
     an I2C stop and return false */
    SWI2C_SDA_HIGH;
    SWI2C_SCL_HIGH;
    TIMER_ITERATION();

    if (SWI2C_PxIN & SWI2C_SDA)
    {
        goto I2CReadTransactionCleanUp;
    }

    /* Next, we want to read out all of the data requested */
    for (ii = 0; ii < size; ii++)
    {
        /*
         * Waiting for our clock line to go high if the slave is stretching
         */
        while (!(SWI2C_PxIN & SWI2C_SCL))
            ;

        /* Setup the read variables */
        temp = 0;
        bits = 0x08;

        /* Sending out another clock cycle */
        SWI2C_SCL_LOW;
        TIMER_ITERATION();
        SWI2C_SDA_HIGH;

        /* Loop to read until all bits have been read */
        do
        {
            /* Priming our temporary variable and sending a clock pulse */
            temp = (temp << 1);
            SWI2C_SCL_HIGH;
            TIMER_ITERATION();

            /* If the data line is high, recording that */
            if (SWI2C_PxIN & SWI2C_SDA)
            {
                temp += 1;
            }

            /* Send out another clock cycle and decrement our counter */
            bits = (bits - 1);
            SWI2C_SCL_LOW;
            TIMER_ITERATION();
        }
        while (bits > 0);

        /* Storing the data off */
        inputArray[ii] = temp;

        /* Now the master needs to send out the ACK */
        if (ii == size - 1)
            SWI2C_SDA_HIGH;
        else
            SWI2C_SDA_LOW;
        SWI2C_SCL_HIGH;

        /*
         * Waiting for our clock line to go high if the slave is stretching
         */
        while (!(SWI2C_PxIN & SWI2C_SCL))
            ;

        TIMER_ITERATION();
    }

    I2CReadTransactionCleanUp:

    /* Sending out the stop bit */
    SWI2C_SCL_LOW;
    SWI2C_SDA_LOW;
    TIMER_ITERATION();
    SWI2C_SCL_HIGH;
    __no_operation();
    SWI2C_SDA_HIGH;
    TIMER_ITERATION();

    /* Stop the timer */
    TB0CTL = MC_0;

    /* If all bytes were read, return true- otherwise false. */
    if (ii == size)
        return true;
    else
        return false;
}
