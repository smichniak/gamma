#ifndef GAMMA_QUEUE_H
#define GAMMA_QUEUE_H

#include <stdint.h>

typedef struct {
    int x;
    int y;

} Tuple;

typedef struct {
    Tuple value;
    struct QueueElement* next;
} QueueElement;

typedef struct {
    QueueElement* first;
    QueueElement* last;
} Queue;

Tuple createTuple(uint32_t x, uint32_t y);

Queue createQueue();

Tuple removeFirst(Queue queue);

void putLast(Tuple element);

void removeQueue(Queue* queue);

#endif //GAMMA_QUEUE_H
