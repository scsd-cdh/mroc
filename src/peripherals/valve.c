/*
 * valve.c
 *
 *  Created on: Feb. 5, 2024
 *      Author: Ruben
 */

#include "valve.h"
#include <src/drivers/drivers.h>

void Valve_Init(Valve_Descriptor *descriptor){
    GPIO_setAsOutputPin(
        descriptor->port,
        descriptor->pin
    );
    Valve_Close(descriptor);
}

void Valve_Open(Valve_Descriptor *descriptor) {
    GPIO_setOutputHighOnPin(
        descriptor->port,
        descriptor->pin
    );
}

void Valve_Close(Valve_Descriptor *descriptor) {
    GPIO_setOutputLowOnPin(
        descriptor->port,
        descriptor->pin
    );
}

