#include "lmt01.h"
#include <src/drivers/drivers.h>

volatile uint16_t pulseCount = 0;
volatile uint16_t currentPulseCount = 0;
volatile uint8_t isCounting = 0;

#define TIMER_PERIOD 50000 // Assuming ACLK or SMCLK is correctly configured
#define PULSE_PIN BIT7     // Assuming P2.7 is the pulse input pin

void LMT01_Init(LMT01_Descriptor *descriptor) {
    // Configure P2.7 as GPIO input with interrupt
    P2DIR &= ~PULSE_PIN;        // Set P2.7 to input direction
    P2IES &= ~PULSE_PIN;        // Interrupt edge select, 0:low-to-high
    P2IE |= PULSE_PIN;          // Enable interrupt on P2.7
    P2IFG &= ~PULSE_PIN;        // Clear interrupt flag

    // Timer0_A setup
    TA0CCTL0 = CCIE;            // Enable Timer0_A interrupt
    TA0CTL = TASSEL__SMCLK + MC_1 + ID1;   // SMCLK, Up mode
    TA0CCR0 = TIMER_PERIOD;     // Set timer count for 50ms interval
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void) {
    if (pulseCount > 400) {
        currentPulseCount = pulseCount;
    }
    pulseCount = 0;
    isCounting = 0;
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    if (P2IFG & PULSE_PIN) {
        pulseCount++;
        P2IFG &= ~PULSE_PIN;
        isCounting = 1;
    }
}

float LMT01_Read() {
    if (pulseCount <= 500) {
        return 0;
    }
    return ((float)currentPulseCount / 4096.0f * 256.0f) - 50.0f;
}
