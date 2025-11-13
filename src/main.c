#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
#include "heap.h"
#include <math.h>

int main() {

    Point points[5] = {
        {3, 6, 2},
        {17, 15, 13},
        {13, 15, 6},
        {6, 12, 20},
        {9, 1, 7}
    };

    MaxHeap* heap = heap_create(10);

    heap_insert(heap, 4, &points[0]);
    heap_insert(heap, 10, &points[0]);
    heap_insert(heap, 3, &points[0]);
    heap_insert(heap, 5, &points[0]);
    heap_insert(heap, 1, &points[0]);
    
    struct Node* p1 = initNode(&points[0], NULL, NULL, NULL);
    struct Node* p2 = initNode(&points[1], NULL, NULL, NULL);
    struct Node* p3 = initNode(&points[2], NULL, NULL, NULL);
    struct Node* p4 = initNode(&points[3], NULL, NULL, NULL);
    struct Node* p5 = initNode(&points[4], NULL, NULL, NULL);



    struct Tree* testTree = initTree();
    tree_insert(testTree, p1);
    tree_insert(testTree, p2);
    tree_insert(testTree, p3);
    tree_insert(testTree, p4);
    tree_insert(testTree, p5);

    printf("%f\n", distSquared(&points[0], &points[1]));

}
