#include <stdlib.h>
#include "heap.h"
#include <stdio.h>

static void heapify_down(MaxHeap *H, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < H->size && H->data[left].dist > H->data[largest].dist)
        largest = left;
    if (right < H->size && H->data[right].dist > H->data[largest].dist)
        largest = right;

    if (largest != i) {
        HeapElem tmp = H->data[i];
        H->data[i] = H->data[largest];
        H->data[largest] = tmp;
        heapify_down(H, largest);
    }
}

static void heapify_up(MaxHeap *H, int i) {
    if (i == 0) return;
    int parent = (i - 1) / 2;
    if (H->data[i].dist > H->data[parent].dist) {
        HeapElem tmp = H->data[i];
        H->data[i] = H->data[parent];
        H->data[parent] = tmp;
        heapify_up(H, parent);
    }
}

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

void heap_insert(MaxHeap *H, double dist, Point *pt) {
    if (H->size < H->capacity) {
        H->data[H->size] = (HeapElem){dist, pt};
        heapify_up(H, H->size);
        H->size++;
    } else if (dist < H->data[0].dist) {
        H->data[0] = (HeapElem){dist, pt};
        heapify_down(H, 0);
    }
}

void heap_free(MaxHeap *H) {
    if (!H) return;
    free(H->data);
    free(H);
}