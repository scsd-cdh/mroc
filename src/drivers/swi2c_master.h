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
#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

/* Pin Definitions. These  should be changed depending on the device that
 * you are using.
 */
#define SWI2C_SCL         BIT3
#define SWI2C_SDA         BIT4
#define SWI2C_PxDIR       P1DIR
#define SWI2C_PxOUT       P1OUT
#define SWI2C_PxIN        P1IN
#define SWI2C_SDA_LOW     SWI2C_PxDIR |= SWI2C_SDA
#define SWI2C_SCL_LOW     SWI2C_PxDIR |= SWI2C_SCL
#define SWI2C_SCL_HIGH    SWI2C_PxDIR &= ~SWI2C_SCL
#define SWI2C_SDA_HIGH    SWI2C_PxDIR &= ~SWI2C_SDA

/* Defines the buffer size to be used. This will change depending on your
 * application and the size requirements for the transfer.
 */

/* Configuration structure for performing an I2C transaction */
typedef struct _SWI2C_I2CTransaction
{
    uint8_t address;
    uint_fast16_t numWriteBytes;
    uint8_t *writeBuffer;
    uint_fast16_t numReadBytes;
    uint8_t *readBuffer;
    bool repeatedStart;
} SWI2C_I2CTransaction;

/* Timer period for determining the clock rate of the I2C data clock. Note that
 * the timer is sourced from SMCLK and that this number is equal to the duration
 * of roughly HALF a clock period. For example, if SMCLK is set to 3MHz and the
 * period below is set to 15, we would end up with an I2C data rate of
 * approximately 100Khz.
 *
 * In short, the I2C data rate frequency can be calculated by:
 *
 * I2C Data Rate =      SMCLK Frequency
 *                    ___________________
 *
 *                      2 * TimerPeriod
 */
#define SWI2C_TIMER_PERIOD  5

/* Macro for a timer iteration */
#define TIMER_ITERATION()            TB0CCTL0 &= ~(CCIFG);           \
                                     while(!(TB0CCTL0 & CCIFG));

/* Function Prototypes */

//*****************************************************************************
//
//! Initializes the software I2C master. This function takes the port
//! definitions that are given above and configures the device for software
//! I2C operation.
//!
//! \return None
//
//*****************************************************************************
extern void SWI2C_initI2C(void);

//*****************************************************************************
//
//! Starts an I2C transaction over the configured I2C master device. Note that
//! this function is blocking until the transaction is completed. If a timeout
//! feature is required, the user should use the watchdog module of their MCU
//! in tandem with this function. Since the I2C slave has the ability to
//! "clock stretch" the module, care has to be taken to manage the real time
//!  behavior of the main application.
//!
//! <hr>
//! <b>Configuration options for \link SWI2C_I2CTransaction \endlink structure.</b>
//! <hr>
//!
//! \param address I2C Slave Address to communicate with.
//! \param numWriteBytes Number of bytes for the master to write
//! \param writeBuffer Pointer to the buffer to write
//! \param numReadBytes Number of bytes to read
//! \param readBuffer Pointer to the buffer to read values into
//! \param repeatedStart In the event that both a read and write operation are
//!         requested, this bool value determines if a repeated start coniditon
//!         is sent out over the bus. If set to true, no I2C STOP is sent out
//!         after the write transaction. If set to false. After the write
//!         transaction completes an I2C STOP condition is sent out, and then
//!         the I2C read transaction is treated as a completely separate
//!         transaction
//!
//! Note that any order of combinations can be passed into the transaction
//! structure. If the user wants to only perform an I2C read, then only the
//! read parameters should be populated and the write parameters should be
//! set to 0 (or vice versa for write). The user can also specify both read
//! and write bytes and use the repeatedStart parameter to specify if there
//! is an I2C STOP between the transactions. Note that the write transaction
//! is always first when using this function.
//!
//! \return true if the operation passed, false otherwise. A false return
//!     value means that the device received a NAK where one was not expected.
//
//*****************************************************************************
extern bool SWI2C_performI2CTransaction(SWI2C_I2CTransaction *i2cTransaction);

