/*
 * cmd_result.h
 *
 *  Created on: Feb. 4, 2024
 *      Author: Ruben
 */

#ifndef SRC_APP_CMD_CMD_RESULT_H_
#define SRC_APP_CMD_CMD_RESULT_H_

typedef enum
{
    TC_SUCCESS,
    TC_NOT_IN_IDLE_MODE,
    TC_UNKNOWN_COMMAND,
    TC_UNKNOWN_EXPERIMENT_PHASE,
    TC_TOO_MANY_ARGUMENTS,
    TC_TOO_FEW_ARGUMENTS,
    TC_TIMEOUT
} TelecommandResult;

#endif /* SRC_APP_CMD_CMD_RESULT_H_ */
