/******************************************************************************

    File Name: main.c
    Description: Contains the entry point for the program.

    Author: Ruben Sanchez
    Date: January 19th, 2024
    Version: 0.1.0

    This file contains <...>. It is part of the <project/system name>
    and is used for <purpose>.

******************************************************************************/

#include <src/app/cmd/cmd_handler.h>
#include <src/app/exp/exp_state_manager.h>
#include <src/app/app.h>
#include <src/drivers/drivers.h>

void main(void) {
    // Stop watchdog
    WDT_A_hold(WDT_A_BASE);

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PMM_unlockLPM5();

    App_Init();
    Exp_Init();
    Cmd_Init();

    while(1) {
        Exp_Update();
        __bis_SR_register(LPM3_bits | GIE);
    }
}
