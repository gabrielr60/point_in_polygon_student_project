#ifndef HEAP_H
#define HEAP_H

#include "point.h"

typedef struct {
    double dist;   
    Point *pt;     
} HeapElem;

typedef struct {
    HeapElem *data;  
    int size;        
    int capacity;    
} MaxHeap;

MaxHeap *heap_create(int capacity);

void heap_insert(MaxHeap *H, double dist, Point *pt);

void heap_free(MaxHeap *H);

#endif