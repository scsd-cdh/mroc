/*
 * app.c
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#include "app.h"
#include <src/drivers/drivers.h>

static volatile AppContext app;

void App_Init() {
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_PJ,
        GPIO_PIN4 | GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    CS_turnOnLFXT(CS_LFXT_DRIVE_3);

    // Initialize Calendar
    Calendar currentTime;
    currentTime.Seconds    = 0x00;
    currentTime.Minutes    = 0x26;
    currentTime.Hours      = 0x13;
    currentTime.DayOfWeek  = 0x03;
    currentTime.DayOfMonth = 0x20;
    currentTime.Month      = 0x07;
    currentTime.Year       = 0x2011;

    RTC_C_initCalendar(RTC_C_BASE,
        &currentTime,
        RTC_C_FORMAT_BCD);

    RTC_C_enableInterrupt(RTC_C_BASE, RTCRDYIE + RTCTEVIE + RTCAIE);
    RTC_C_enableInterrupt(RTC_C_BASE, RTCRDYIFG);
    RTC_C_startClock(RTC_C_BASE);
}

uint32_t App_GetUptime() {
    return app.uptime_seconds;
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_C_ISR (void)
{
    switch (__even_in_range(RTCIV,16)){
        case RTCIV_NONE: break;
        case RTCIV_RTCOFIFG: break;
        case RTCIV_RTCRDYIFG:
            app.uptime_seconds ++;
            __bic_SR_register_on_exit(LPM3_bits);
            break;
        case RTCIV_RTCTEVIFG: break;
        case RTCIV_RTCAIFG: break;
        case RTCIV_RT0PSIFG: break;
        case RTCIV_RT1PSIFG: break;
        default: break;
    }
}
