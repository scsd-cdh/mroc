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
            descriptor->pump_forward_p_port,
            descriptor->pump_forward_p_pin
        );

    GPIO_setAsOutputPin(
              descriptor->pump_forward_n_port,
              descriptor->pump_forward_n_pin
          );

    GPIO_setAsOutputPin(
              descriptor->pump_backward_p_port,
              descriptor->pump_backward_p_pin
          );

    GPIO_setAsOutputPin(
              descriptor->pump_backward_n_port,
              descriptor->pump_backward_n_pin
          );

    descriptor->state=OFF;
}

void Bipump_Forward(Bipump_Descriptor *descriptor){
//Q2:low, Q1: high
//Q6: high, Q5: low
    GPIO_setOutputLowOnPin(
          descriptor->pump_forward_p_port,
          descriptor->pump_forward_p_pin
      );
    GPIO_setOutputHighOnPin(
            descriptor->pump_forward_n_port,
            descriptor->pump_forward_n_pin
           );
    GPIO_setOutputHighOnPin(
            descriptor->pump_backward_p_port,
            descriptor->pump_backward_p_pin
        );
      GPIO_setOutputLowOnPin(
           descriptor->pump_backward_n_port,
           descriptor->pump_backward_n_pin
             );
      descriptor->state=FORWARD;
}

void Bipump_Backward(Bipump_Descriptor *descriptor){
    //Q2:high, Q1: low
    //Q6: low, Q5: high
    GPIO_setOutputHighOnPin(
          descriptor->pump_forward_p_port,
          descriptor->pump_forward_p_pin
      );
    GPIO_setOutputLowOnPin(
            descriptor->pump_forward_n_port,
            descriptor->pump_forward_n_pin
           );
    GPIO_setOutputLowOnPin(
            descriptor->pump_backward_p_port,
            descriptor->pump_backward_p_pin
        );
      GPIO_setOutputHighOnPin(
           descriptor->pump_backward_n_port,
           descriptor->pump_backward_n_pin
             );
      descriptor->state=BACKWARD;
}

void Bipump_TurnOff(Bipump_Descriptor *descriptor){
    //Q2:high, Q1: high
    //Q6:low, Q5: low
    GPIO_setOutputHighOnPin(
             descriptor->pump_forward_p_port,
             descriptor->pump_forward_p_pin
         );
       GPIO_setOutputLowOnPin(
               descriptor->pump_forward_n_port,
               descriptor->pump_forward_n_pin
              );
       GPIO_setOutputHighOnPin(
               descriptor->pump_backward_p_port,
               descriptor->pump_backward_p_pin
           );
         GPIO_setOutputLowOnPin(
              descriptor->pump_backward_n_port,
              descriptor->pump_backward_n_pin
                );
         descriptor->state=OFF;
}


