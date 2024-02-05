/*
 * cmd_handler.h
 *
 *  Created on: Feb. 3, 2024
 *      Author: Ruben
 */

#ifndef SRC_CMD_CMD_HANDLER_H_
#define SRC_CMD_CMD_HANDLER_H_

#include "cmd_list.h"
#include "cmd_result.h"
#include <stdint.h>
#include "cmd_register.h"

// TODO: update MAX_CMD_SIZE to the actual size
#define MAX_CMD_SIZE 255

typedef enum
{
    LISTENER_TC_RECEIVED, LISTENER_TC_PARSED, LISTENER_TLM_RECEIVED, LISTENER_SLEEP
} Cmd_ListenerState;

void Cmd_Init();

#endif /* SRC_CMD_CMD_HANDLER_H_ */
