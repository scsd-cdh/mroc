/******************************************************************************

    File Name: main.c
    Description: Contains the entry point for the program.

    Author: Ruben Sanchez
    Date: January 19th, 2024
    Version: 1

******************************************************************************/

#include <src/app/cmd/cmd_handler.h>
#include <src/app/exp/exp_state_manager.h>
#include <src/app/app.h>
#include <src/drivers/drivers.h>
#include <src/config.h>

void main(void) {
    WDT_A_hold(WDT_A_BASE);     // Stop watchdog
    PMM_unlockLPM5();           // Disable the GPIO power-on default high-impedance mode

    App_Init();
    Exp_Init();
    Cmd_Init();

    while(1) {
        Exp_Update();
        __bis_SR_register(LPM1_bits | GIE);
    }
}
