/*
 * Priority queue lib.
 */

#include "priority_queue.h"


/*
 * min_heapify():
 *      Input: integer array, array size, starting array index for heapify
 *      Output: No return value. The heapification is performed in-place and recursively.
 */
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

/*
 * max_heapify():
 *      Input: integer array, array size, starting array index for heapify
 *      Output: No return value. The heapification is performed in-place and recursively.
 */
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

/*
 * pq_init(): Initialize the queue
 *      Input: boolean to indicate whether to use min-heapify or max-heapify.
 *      Output: Pointer to object of type priority_queue_t.
 */
priority_queue_t *pq_init (bool min_heap)
{
    priority_queue_t *obj = calloc(1, sizeof(priority_queue_t));
    obj->min_heap = min_heap;
    obj->size = DEFAULT_PQ_SIZE; //Default initial size of the queue
    obj->count = 0;
    obj->q = calloc(DEFAULT_PQ_SIZE, sizeof(int));
    return (obj);
}

/*
 * pq_destroy(): Release all allocated memory.
 *      Input: Pointer to object of type priority_queue_t.
 *      Output: None.
 */
void pq_destroy (priority_queue_t *obj)
{
    free(obj->q);
    free(obj);
}

/*
 * pq_is_empty(): Check is the queue is empty
 *      Input: Pointer to object of type priority_queue_t.
 *      Output: true or false.
 */
bool pq_is_empty (priority_queue_t *obj)
{
    return (obj->count == 0);
}

/*
 * pq_get_size(): Check the current queue size. Please note that this is to check queue
 *                and not the number of elements that are pushed into the queue. Also, 
 *                keep in mind that the queue size can change dynamically.
 *      Input: Pointer to object of type priority_queue_t.
 *      Output: Integer value of current queue size.
 */
int pq_get_size (priority_queue_t *obj)
{
    return (obj->size);
}

/*
 * pq_get_count(): Check the number of elements that are so far inserted into the queue.
 *      Input: Pointer to object of type priority_queue_t.
 *      Output: Integer number of current items into the queue.
 */
int pq_get_count (priority_queue_t *obj)
{
    return (obj->count);
}

/*
 * pq_peek(): Peek the element at 0th index of the queue.
 *      Input: Pointer to object of type priority_queue_t.
 *      Output: Integer number of current items into the queue.
 */
int pq_peek (priority_queue_t *obj)
{
    return (obj->q[0]);
}

/*
 * pq_push(): Push a new element into heap.
 *      Input: Pointer to object of type priority_queue_t and integer item to be inserted.
 *      Output: No return value.
 */
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

/*
 * pq_pop(): Retrieve the element from 0th index of the queue.
 *      Input: Pointer to object of type priority_queue_t and integer item to be inserted.
 *      Output: Integer number of current items into the queue.
 */
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

