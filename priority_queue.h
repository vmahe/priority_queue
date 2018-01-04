
#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_PQ_SIZE  50

typedef struct priority_queue_t_ {
    bool min_heap;
    int size;
    int count;
    int *q;
} priority_queue_t;

static inline void swap (int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

#endif //PRIORITY_QUEUE_H_

