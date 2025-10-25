#ifndef KDTREE_H
#define KDTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    float x;
    float y;
    float z;

    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
};

struct Tree {
    struct Node *root;
    int nNodes;
};

struct Node* initNode(float x, float y, float z,
              struct Node *p,
              struct Node *lc,
              struct Node *rc);

struct tree* initTree(void);

void tree_insert(struct tree* t, struct Node* n);

#endif
