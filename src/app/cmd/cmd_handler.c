/*
 * cmd_handler.c
 *
 *  Created on: Feb. 3, 2024
 *      Author: Ruben
 */
#include <stdint.h>
#include <src/app/exp/exp_state_manager.h>
#include <src/drivers/drivers.h>
#include <src/config.h>
#include "cmd_list.h"
#include "cmd_result.h"
#include "cmd_register.h"
#include "cmd_handler.h"

// TODO: update MAX_CMD_SIZE to the actual size
#define MAX_CMD_SIZE 255

static uint8_t commandArgumentBuffer[MAX_CMD_SIZE] = {0};
static uint8_t commandArgumentBufferLength;
static uint8_t commandArgumentBufferIdx;
static uint8_t command;

static Cmd_ListenerState commandListenerState;

void Cmd_Init()
{
    // Initialize static variables
    command = CMD_UNDEFINED;
    commandArgumentBufferIdx = 0;

    //Set DCO frequency to 1MHz
    CS_setDCOFreq(CS_DCORSEL_0,CS_DCOFSEL_0);
    //Set ACLK = VLO with frequency divider of 1
    CS_initClockSignal(CS_ACLK,CS_VLOCLK_SELECT,CS_CLOCK_DIVIDER_1);
    //Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_SMCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);
    //Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_MCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);

    // Initialize communication protocol
    // Main I2C Bus
    GPIO_setAsPeripheralModuleFunctionInputPin(MAIN_I2C_PORT,
                                               MAIN_I2C_SDA + MAIN_I2C_SCL,
                                               GPIO_PRIMARY_MODULE_FUNCTION);

    EUSCI_B_I2C_initSlaveParam param = { 0 };
    param.slaveAddress = MAIN_SLAVE_ADDR;
    param.slaveAddressOffset = EUSCI_B_I2C_OWN_ADDRESS_OFFSET0;
    param.slaveOwnAddressEnable = EUSCI_B_I2C_OWN_ADDRESS_ENABLE;
    EUSCI_B_I2C_initSlave(EUSCI_B0_BASE, &param);

    EUSCI_B_I2C_enable(EUSCI_B0_BASE);

    EUSCI_B_I2C_clearInterrupt(EUSCI_B0_BASE,
                               EUSCI_B_I2C_CLOCK_LOW_TIMEOUT_INTERRUPT +
                               EUSCI_B_I2C_RECEIVE_INTERRUPT0 +
                               EUSCI_B_I2C_TRANSMIT_INTERRUPT0 +
                               EUSCI_B_I2C_STOP_INTERRUPT);

    EUSCI_B_I2C_enableInterrupt(EUSCI_B0_BASE,
                                EUSCI_B_I2C_CLOCK_LOW_TIMEOUT_INTERRUPT+
                                EUSCI_B_I2C_RECEIVE_INTERRUPT0 +
                                EUSCI_B_I2C_TRANSMIT_INTERRUPT0 +
                                EUSCI_B_I2C_STOP_INTERRUPT);

}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_B0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_B0_VECTOR)))
#endif
void USCIB0_ISR(void)
{
    switch (__even_in_range(UCB0IV, USCI_I2C_UCBIT9IFG))
    {
    case USCI_NONE:             // No interrupts break;
        break;
    case USCI_I2C_UCALIFG:      // Arbitration lost
        break;
    case USCI_I2C_UCNACKIFG:    // NAK received (master only)
        break;
    case USCI_I2C_UCSTTIFG:     // START condition detected with own address (slave mode only)
        break;
    case USCI_I2C_UCSTPIFG:     // STOP condition detected (master & slave mode)
        if (commandArgumentBufferIdx != commandArgumentBufferLength) {
            Cmd_SetTelecommandAcknowledge(command, TC_TOO_FEW_ARGUMENTS);
        }
        commandListenerState = LISTENER_SLEEP;
        command = CMD_UNDEFINED;
        break;
    case USCI_I2C_UCRXIFG3:     // RXIFG3
        break;
    case USCI_I2C_UCTXIFG3:     // TXIFG3
        break;
    case USCI_I2C_UCRXIFG2:     // RXIFG2
        break;
    case USCI_I2C_UCTXIFG2:     // TXIFG2
        break;
    case USCI_I2C_UCRXIFG1:     // RXIFG1
        break;
    case USCI_I2C_UCTXIFG1:     // TXIFG1
        break;
    case USCI_I2C_UCRXIFG0:     // RXIFG0
        if (commandListenerState == LISTENER_SLEEP) {
            command = EUSCI_B_I2C_slaveGetData(EUSCI_B0_BASE);
            if (command < CMD_TC_MAX) {
               commandListenerState = LISTENER_TC_RECEIVED;

               switch(command) {
               case CMD_NEXT_EXPERIMENT_PHASE:
                   if (State_IsIdle()) {
                       Exp_NextState();
                   } else {
                       Cmd_SetTelecommandAcknowledge(command, TC_NOT_IN_IDLE_MODE);
                   }

                   commandListenerState = LISTENER_TC_PARSED;
                   break;
               case CMD_RUN_EXPERIMENT_PHASE:
                   commandArgumentBufferLength = 1;
                   break;
               case CMD_SET_LED_STATE:
                   commandArgumentBufferLength = 1;
                   break;
               case CMD_TEST_SYSTEM_HEALTH:
                   commandListenerState = LISTENER_TC_PARSED;
                   break;
               case CMD_SET_STATE_IDLE:
                   Exp_SetIdle();
                   commandListenerState = LISTENER_TC_PARSED;
                   break;
               case CMD_RESET:
                   commandListenerState = LISTENER_TC_PARSED;
                   break;
               default:
                   break;
               }
            } else {
                Cmd_RequestTelemetryFrame(command);
                commandListenerState = LISTENER_TLM_RECEIVED;
            }
        } else if (commandListenerState == LISTENER_TC_RECEIVED) {
            commandArgumentBuffer[commandArgumentBufferIdx++] = EUSCI_B_I2C_slaveGetData(EUSCI_B0_BASE);

            if(commandArgumentBufferIdx == commandArgumentBufferLength) {
                switch(command) {
                case CMD_RUN_EXPERIMENT_PHASE:
                    if (State_IsIdle()) {
                       Exp_SetState(commandArgumentBuffer[0]);
                   } else {
                       Cmd_SetTelecommandAcknowledge(command, TC_NOT_IN_IDLE_MODE);
                   }
                   break;
                case CMD_SET_LED_STATE:
                    commandArgumentBufferLength = 1;
                    break;
                default:
                    break;
                }
            }
        } else if (commandListenerState == LISTENER_TC_PARSED) {
            Cmd_SetTelecommandAcknowledge(command, TC_TOO_MANY_ARGUMENTS);
        }
        break;
    case USCI_I2C_UCTXIFG0:     // TXIFG0
        EUSCI_B_I2C_slavePutData(EUSCI_B0_BASE, Cmd_ReadRegister());
        break;
    case USCI_I2C_UCBCNTIFG:    // Byte count limit reached (UCBxTBCNT)
        break;
    case USCI_I2C_UCCLTOIFG:    // Clock low timeout - clock held low too long
        Cmd_SetTelecommandAcknowledge(command, TC_TIMEOUT);
        commandListenerState = LISTENER_SLEEP;
        command = CMD_UNDEFINED;
        break;
    case USCI_I2C_UCBIT9IFG: // Generated on 9th bit of a transmit (for debugging)
        break;
    default:
        break;
    }
}

