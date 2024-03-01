/*
 * bipump.c
 *
 *  Created on: Feb 5, 2024
 *      Author: space
 */

#include "bipump.h"
#include <src/drivers/drivers.h>

void Bipump_Init(Bipump_Descriptor *descriptor) {
    GPIO_setAsOutputPin(
        descriptor->pump_q2_port,
        descriptor->pump_q2_pin
    );
    GPIO_setAsOutputPin(
        descriptor->pump_q1_port,
        descriptor->pump_q1_pin
    );
    GPIO_setAsOutputPin(
        descriptor->pump_q6_port,
        descriptor->pump_q6_pin
    );
    GPIO_setAsOutputPin(
        descriptor->pump_q5_port,
        descriptor->pump_q5_pin
    );

    Bipump_Off(descriptor);
}

void Bipump_Forward(Bipump_Descriptor *descriptor){
    //Q2:low, Q1: high
    //Q6: high, Q5: low
    GPIO_setOutputLowOnPin(
        descriptor->pump_q2_port,
        descriptor->pump_q2_pin
    );
    GPIO_setOutputHighOnPin(
        descriptor->pump_q1_port,
        descriptor->pump_q1_pin
    );
    GPIO_setOutputHighOnPin(
        descriptor->pump_q6_port,
        descriptor->pump_q6_pin
    );
    GPIO_setOutputLowOnPin(
        descriptor->pump_q5_port,
        descriptor->pump_q5_pin
    );

    descriptor->state=FORWARD;
}

void Bipump_Backward(Bipump_Descriptor *descriptor){
    //Q2:high, Q1: low
    //Q6: low, Q5: high
    GPIO_setOutputHighOnPin(
        descriptor->pump_q2_port,
        descriptor->pump_q2_pin
    );
    GPIO_setOutputLowOnPin(
        descriptor->pump_q1_port,
        descriptor->pump_q1_pin
    );
    GPIO_setOutputLowOnPin(
        descriptor->pump_q6_port,
        descriptor->pump_q6_pin
    );
    GPIO_setOutputHighOnPin(
        descriptor->pump_q5_port,
        descriptor->pump_q5_pin
    );

    descriptor->state=BACKWARD;
}

void Bipump_Off(Bipump_Descriptor *descriptor){
    //Q2:high, Q1: high
    //Q6:low, Q5: low
    GPIO_setOutputHighOnPin(
        descriptor->pump_q2_port,
        descriptor->pump_q2_pin
    );
    GPIO_setOutputHighOnPin(
        descriptor->pump_q1_port,
        descriptor->pump_q1_pin
    );
    GPIO_setOutputLowOnPin(
        descriptor->pump_q6_port,
        descriptor->pump_q6_pin
    );
    GPIO_setOutputLowOnPin(
        descriptor->pump_q5_port,
        descriptor->pump_q5_pin
    );

    descriptor->state=OFF;
}


