#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

const int INITIAL_QUEUE_SIZE = 16;

Tuple createTuple(uint32_t x, uint32_t y){
    Tuple newTuple;
    newTuple.x = x;
    newTuple.y = y;
    return newTuple;
}

Queue createQueue(){
    Queue newQueue;
    newQueue.first = NULL;
    newQueue.last = NULL;
    return newQueue;
}

