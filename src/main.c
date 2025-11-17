#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
#include "heap.h"
#include <math.h>

int main() {

    Point points[10] = {
    {13, 15, 6},
    {6, 12, 20},
    {17, 15, 13},
    {9, 1, 7},
    {3, 6, 2},
    {25, 30, 10},
    {0, 0, 1},
    {8, 9, 3},
    {14, 2, 9},
    {5, 25, 17}
};

    MaxHeap* heap = heap_create(5);
    
    struct Node* p1 = initNode(&points[0], NULL, NULL, NULL);
    struct Node* p2 = initNode(&points[1], NULL, NULL, NULL);
    struct Node* p3 = initNode(&points[2], NULL, NULL, NULL);
    struct Node* p4 = initNode(&points[3], NULL, NULL, NULL);
    struct Node* p5 = initNode(&points[4], NULL, NULL, NULL);
    struct Node* p6 = initNode(&points[5], NULL, NULL, NULL);
    struct Node* p7 = initNode(&points[6], NULL, NULL, NULL);
    struct Node* p8 = initNode(&points[7], NULL, NULL, NULL);
    struct Node* p9 = initNode(&points[8], NULL, NULL, NULL);
    struct Node* p10 = initNode(&points[9], NULL, NULL, NULL);

    Point q = {0, 0, 0};

    struct  Node* qNode = initNode(&q, NULL, NULL, NULL);

    struct Tree* testTree = initTree();
    tree_insert(testTree, p1);
    tree_insert(testTree, p2);
    tree_insert(testTree, p3);
    tree_insert(testTree, p4);
    tree_insert(testTree, p5);
    tree_insert(testTree, p6);
    tree_insert(testTree, p7);
    tree_insert(testTree, p8);
    tree_insert(testTree, p9);
    tree_insert(testTree, p10);

    pClosest(heap, testTree->root, &q, 0);

    printf("[ %f , %f , %f], %f\n", heap->data[0].pt->x, heap->data[0].pt->y, heap->data[0].pt->z, heap->data[0].dist);
    printf("[ %f , %f , %f], %f\n", heap->data[1].pt->x, heap->data[1].pt->y, heap->data[1].pt->z, heap->data[1].dist);
    printf("[ %f , %f , %f], %f\n", heap->data[2].pt->x, heap->data[2].pt->y, heap->data[2].pt->z, heap->data[2].dist);
    printf("[ %f , %f , %f], %f\n", heap->data[3].pt->x, heap->data[3].pt->y, heap->data[3].pt->z, heap->data[3].dist);
    printf("[ %f , %f , %f], %f\n", heap->data[4].pt->x, heap->data[4].pt->y, heap->data[4].pt->z, heap->data[4].dist);
    

}
