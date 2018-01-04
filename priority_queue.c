/*
 * Priority queue lib.
 */

#include "priority_queue.h"


static void min_heapify (int *arr, int n, int i)
{
    int min = i;
    int l = (2*i) + 1;
    int r = (2*i) + 2;
    
    if (l < n && arr[l] < arr[min]) min = l;
    if (r < n && arr[r] < arr[min]) min = r;
    if (min != i) {
        swap(&arr[min], &arr[i]);
        min_heapify(arr, n, min);
    }
}

static void max_heapify (int *arr, int n, int i)
{
    int max = i;
    int l = (2*i) + 1;
    int r = (2*i) + 2;
    
    if (l < n && arr[l] > arr[max]) max = l;
    if (r < n && arr[r] > arr[max]) max = r;
    if (max != i) {
        swap(&arr[max], &arr[i]);
        max_heapify(arr, n, max);
    }
}

priority_queue_t *pq_init (bool min_heap)
{
    priority_queue_t *obj = calloc(1, sizeof(priority_queue_t));
    obj->min_heap = min_heap;
    obj->size = DEFAULT_PQ_SIZE;
    obj->count = 0;
    obj->q = calloc(DEFAULT_PQ_SIZE, sizeof(int));
    return (obj);
}

void pq_destroy (priority_queue_t *obj)
{
    free(obj->q);
    free(obj);
}

bool pq_is_empty (priority_queue_t *obj)
{
    return (obj->count == 0);
}

int pq_get_size (priority_queue_t *obj)
{
    return (obj->size);
}

int pq_get_count (priority_queue_t *obj)
{
    return (obj->count);
}

int pq_peek (priority_queue_t *obj)
{
    return (obj->q[0]);
}

void pq_push (priority_queue_t *obj, int num)
{
    int i;
    
    if (obj->count == obj->size) {
        obj->q = realloc(obj->q, obj->size*2*sizeof(int));
        obj->size *= 2;
    }
    
    obj->q[obj->count] = num;
    obj->count++;
    
    i = obj->count - 1;
    if (obj->min_heap) {
        while (i != 0 && obj->q[i] < obj->q[(i-1)/2]) {
            swap(&(obj->q[i]), &(obj->q[(i-1)/2]));
            i = (i-1)/2;
        }
    } else {
        while (i != 0 && obj->q[i] > obj->q[(i-1)/2]) {
            swap(&(obj->q[i]), &(obj->q[(i-1)/2]));
            i = (i-1)/2;
        }
    }
}

int pq_pop (priority_queue_t *obj)
{
    int ret = obj->q[0];
    
    obj->count--;
    obj->q[0] = obj->q[obj->count];
    if (obj->size > DEFAULT_PQ_SIZE && obj->count*4 <= obj->size) {
        obj->q = realloc(obj->q, (obj->size/2)*sizeof(int));
        obj->size /= 2;
    }
    
    if (obj->min_heap) {
        min_heapify(obj->q, obj->count, 0);
    } else {
        max_heapify(obj->q, obj->count, 0);
    }
    
    return (ret);
}

