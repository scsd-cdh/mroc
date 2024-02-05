/*
 * pump.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_PERIPHERALS_PUMP_H_
#define SRC_PERIPHERALS_PUMP_H_

typedef enum
{
    FEEDING_PUMP, MIXING_PUMP
} PumpIdentifier;

void Pump_Init();
void Pump_Start(PumpIdentifier id);
void Pump_Stop(PumpIdentifier id);

#endif /* SRC_PERIPHERALS_PUMP_H_ */
