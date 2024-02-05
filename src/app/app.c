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
    Calendar currentTime;

    // Configure PJ.4 and PJ.5 as input pins for LFXIN and LFXOUT mode
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_PJ,
        GPIO_PIN4 | GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    //Initialize LFXT1
    CS_turnOnLFXT(
        CS_LFXT_DRIVE_3
        );

    //Setup Current Time for Calendar
    currentTime.Seconds    = 0x00;
    currentTime.Minutes    = 0x26;
    currentTime.Hours      = 0x13;
    currentTime.DayOfWeek  = 0x03;
    currentTime.DayOfMonth = 0x20;
    currentTime.Month      = 0x07;
    currentTime.Year       = 0x2011;

    //Initialize Calendar Mode of RTC
    /*
     * Base Address of the RTC_B
     * Pass in current time, intialized above
     * Use BCD as Calendar Register Format
     */
    RTC_B_initCalendar(RTC_B_BASE,
        &currentTime,
        RTC_B_FORMAT_BCD);

    //Setup Calendar Alarm for 5:00pm on the 5th day of the week.
    //Note: Does not specify day of the week.
    RTC_B_configureCalendarAlarmParam param = {0};
    param.minutesAlarm = 0x00;
    param.hoursAlarm = 0x17;
    param.dayOfWeekAlarm = RTC_B_ALARMCONDITION_OFF;
    param.dayOfMonthAlarm = 0x05;
    RTC_B_configureCalendarAlarm(RTC_B_BASE, &param);

    //Specify an interrupt to assert every minute
    RTC_B_setCalendarEvent(RTC_B_BASE,
        RTC_B_CALENDAREVENT_MINUTECHANGE);

    RTC_B_clearInterrupt(RTC_B_BASE,
        RTC_B_CLOCK_READ_READY_INTERRUPT +
        RTC_B_TIME_EVENT_INTERRUPT +
        RTC_B_CLOCK_ALARM_INTERRUPT
        );
    //Enable interrupt for RTC Ready Status, which asserts when the RTC
    //Calendar registers are ready to read.
    //Also, enable interrupts for the Calendar alarm and Calendar event.
    RTC_B_enableInterrupt(RTC_B_BASE,
        RTC_B_CLOCK_READ_READY_INTERRUPT +
        RTC_B_TIME_EVENT_INTERRUPT +
        RTC_B_CLOCK_ALARM_INTERRUPT
        );

    //Start RTC Clock
    RTC_B_startClock(RTC_B_BASE);
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
void RTC_B_ISR (void)
{
    switch (__even_in_range(RTCIV,16)){
        case 0: break;  //No interrupts
        case 2:         //RTCRDYIFG
            app.uptime_seconds ++;
            __bic_SR_register_on_exit(LPM3_bits);
            break;
        case 4: break;  //RTCEVIFG
        case 6: break;  //RTCAIFG
        case 8: break;  //RT0PSIFG
        case 10: break; //RT1PSIFG
        case 12: break; //Reserved
        case 14: break; //Reserved
        case 16: break; //Reserved
        default: break;
    }
}
