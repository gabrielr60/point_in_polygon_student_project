#ifndef HEAP_H
#define HEAP_H

#include "point.h"

/*
 * Max-heap for storing the k closest points found so far in neigbours search.
 * Stores distance to ceratin point and the pointindex.
 * Ordering after distance.
*/

/* Element stored in the heap: distance and corresponding point index. */
typedef struct {
    double dist;    
    int pointIndex;     
} HeapElem;

/* Max-heap structure. */
typedef struct {
    HeapElem *data;     // Array of heap elements
    int size;           // Current number of elements in the heap
    int capacity;       // Storage capacity
} MaxHeap;

/*Create a new heap with the specified capacity.*/
MaxHeap *heap_create(int capacity);

/*Insert a new element if heap not full or new element samller then max element.*/
void heap_insert(MaxHeap *H, double dist, int newPointIndex);

/*Free memory from heap.*/
void heap_free(MaxHeap *H);

#endif
