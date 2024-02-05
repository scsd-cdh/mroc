/*
 * err.h
 *
 *  Created on: Feb. 2, 2024
 *      Author: Ruben
 */

#ifndef SRC_RESULT_H_
#define SRC_RESULT_H_

typedef enum
{
    SUCCESS,
    ERR_BUFFER_NULL,
    ERR_CIRCULAR_BUFFER_FULL,
    ERR_CIRCULAR_BUFFER_EMPTY,
} Result;

#endif /* SRC_RESULT_H_ */
