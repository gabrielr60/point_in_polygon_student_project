#include <stdio.h>
#include <stdlib.h>
#include "/home/elias/cprojects/lidarCode/include/kdtree.h"
#include <math.h>

int main() {

    Point points[5] = {
        {3, 6, 2},
        {17, 15, 13},
        {13, 15, 6},
        {6, 12, 20},
        {9, 1, 7}
    };
    
    struct Node* p1 = initNode(&points[0], NULL, NULL, NULL);
    struct Node* p2 = initNode(&points[1], NULL, NULL, NULL);
    struct Node* p3 = initNode(&points[2], NULL, NULL, NULL);

    struct Tree* testTree = initTree();
    tree_insert(testTree, p1);
    tree_insert(testTree, p2);
    tree_insert(testTree, p3);

    printf("%f\n", testTree->root->rightChild->coords->x);

}