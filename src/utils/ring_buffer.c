#include <src/utils/ring_buffer.h>

Result RingBuffer_Enqueue(RingBuffer *buffer, uint8_t data)
{
    if (buffer->count < RING_BUFFER_SIZE)
    {
        buffer->data[buffer->head] = data;
        buffer->head = (buffer->head + 1) % RING_BUFFER_SIZE;
        buffer->count++;
        return SUCCESS;
    }
    else
    {
        return ERR_CIRCULAR_BUFFER_FULL;
    }
}

Result RingBuffer_Dequeue(RingBuffer *buffer, uint8_t *data)
{
    if (buffer->count > 0)
    {
        *data = buffer->data[buffer->tail];
        buffer->tail = (buffer->tail + 1) % RING_BUFFER_SIZE;
        buffer->count--;

        return SUCCESS;
    }
    else
    {
        return ERR_CIRCULAR_BUFFER_EMPTY;
    }
}

Result RingBuffer_Peek(RingBuffer *buffer, uint8_t *data)
{
    if (buffer->count > 0)
    {
        *data = buffer->data[buffer->tail];
        return SUCCESS;
    }
    else
    {
        return ERR_CIRCULAR_BUFFER_EMPTY;
    }
}
