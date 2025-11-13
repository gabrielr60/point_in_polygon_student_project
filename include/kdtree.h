#ifndef KDTREE_H
#define KDTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"
#include "heap.h"

struct Node {
    Point* coords;
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
};

struct Tree {
    struct Node *root;
    int nNodes;
};

struct Node* initNode(Point* coords,
              struct Node *p,
              struct Node *lc,
              struct Node *rc);

struct Tree* initTree(void);

void tree_insert(struct Tree* t, struct Node* n);

void pClosest(MaxHeap* topp, struct Tree * t, struct Node* start, Point *q, int p, int i);

#endif
