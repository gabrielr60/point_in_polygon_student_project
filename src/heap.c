#include <stdlib.h>
#include "heap.h"
#include <stdio.h>

/* Reestablish max-heap property by pushing down element at index i.*/
static void heapify_down(MaxHeap *H, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    // Find largest among node and children (if within bounds)
    if (left < H->size && H->data[left].dist > H->data[largest].dist)
        largest = left;
    if (right < H->size && H->data[right].dist > H->data[largest].dist)
        largest = right;

    // swap if child is larger and continue down the tree
    if (largest != i) {
        HeapElem tmp = H->data[i];
        H->data[i] = H->data[largest];
        H->data[largest] = tmp;
        heapify_down(H, largest);
    }
}

/*Restore the max-heap property letting element at index "float up".*/
static void heapify_up(MaxHeap *H, int i) {
    if (i == 0) return;  // root reached
    int parent = (i - 1) / 2;

    // If child is larger than parent, swap and continue upward
    if (H->data[i].dist > H->data[parent].dist) {
        HeapElem tmp = H->data[i];
        H->data[i] = H->data[parent];
        H->data[parent] = tmp;
        heapify_up(H, parent);
    }
}

/* Allocate a new max-heap*/
MaxHeap *heap_create(int capacity) {
    MaxHeap *H = malloc(sizeof(MaxHeap));
    if (!H) return NULL;

    H->data = malloc(sizeof(HeapElem) * capacity);
    if (!H->data) {
        free(H);
        return NULL;
    }

    H->size = 0;
    H->capacity = capacity;
    return H;
}

/*
 * Insert (dist, newPointIndex) into the heap.
 * Only inserts if heap not full or samaller then max element. 
*/
void heap_insert(MaxHeap *H, double dist, int newPointIndex) {
    if (H->size < H->capacity) {
        //append and bubble up
        H->data[H->size] = (HeapElem){dist, newPointIndex};
        heapify_up(H, H->size);
        H->size++;
    } else if (dist < H->data[0].dist) {
        // Replace maximum only if the new key is smaller
        H->data[0] = (HeapElem){dist, newPointIndex};
        heapify_down(H, 0);
    }
}

/*Free all heap memory.*/
void heap_free(MaxHeap *H) {
    if (!H) return;
    free(H->data);
    free(H);
}
