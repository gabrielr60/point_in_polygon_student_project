#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
#include "heap.h"
#include <math.h>


int main() {
	
    Point points[10] = {
        {1,2,3}, {4,5,6}, {7,8,9}, {2,3,1}, {6,5,4},
        {9,8,7}, {3,1,2}, {5,6,4}, {8,7,9}, {0,0,0}
    };

    struct Tree* t = initTree(10);

    for (int i = 0; i<10; i++){
        t->data[i].coords = points[i];
        if (i > 0){
            tree_insert(t, i);
        }
    }
    
    MaxHeap* H = heap_create(3);

    pClosest(t, H, 0, 3, 0);

    Point p0 = t->data[H->data[0].pointIndex].coords;
    Point p1 = t->data[H->data[1].pointIndex].coords;
    Point p2 = t->data[H->data[2].pointIndex].coords;

    printf("%f, %f, %f\n", p0.x, p0.y, p0.z);
    printf("%f, %f, %f\n", p1.x, p1.y, p1.z);
    printf("%f, %f, %f\n", p2.x, p2.y, p2.z);
    
}
