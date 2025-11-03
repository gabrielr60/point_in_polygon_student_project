#ifndef KDTREE_H
#define KDTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} Point;

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

#endif
