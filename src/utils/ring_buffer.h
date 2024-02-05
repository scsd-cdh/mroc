/*
 * drv_led.h
 *
 *  Created on: Feb. 2, 2024
 *      Author: Ruben
 */

#ifndef SRC_UTILS_RING_BUFFER_H_
#define SRC_UTILS_RING_BUFFER_H_

#include <stdint.h>
#include "../config.h"
#include "result.h"

typedef struct
{
    uint8_t data[RING_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} RingBuffer;

Result RingBuffer_Enqueue(RingBuffer *buffer, uint8_t data);
Result RingBuffer_Dequeue(RingBuffer *buffer, uint8_t *data);
Result RingBuffer_Peek(RingBuffer *buffer, uint8_t *data);

#endif /* SRC_UTILS_RING_BUFFER_H_ */
