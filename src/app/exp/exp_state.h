/*
 * state.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_EXP_EXP_STATE_H_
#define SRC_APP_EXP_EXP_STATE_H_

#include <stdint.h>

#define STATE_IDLE 0
#define STATE_PREPARATION 1
#define STATE_ACTIVATION 2
#define STATE_GROWTH 3
#define STATE_INDUCTION 4
#define MAX_STATE 5

typedef enum
{
    STATE_INCOMPLETE, STATE_COMPLETE
} StateProgress;

#endif /* SRC_APP_EXP_EXP_STATE_H_ */
