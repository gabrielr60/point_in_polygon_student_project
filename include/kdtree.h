#ifndef KDTREE_H
#define KDTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"
#include "heap.h"

/*
*implementation of a KD-tree to store points red from LiDAR file.
*/

/*Nodes in the KD tree storing points and indecees of children*/
struct Node {
    Point coords;
    int leftChildIndex;
    int rightChildIndex;
};

/*Structure storing the KD-tree*/
struct Tree {
    struct Node* data; //array of nodes
    int nNodes; //number of nodes in the tree
    int capacity; //maxcapacity 
};

/*Initialize tree with certain capacity*/
struct Tree* initTree(int capacity);

/*Insert a point in the tree*/
void tree_insert(struct Tree* t, int newPointIndex);

/*Recursive function that fills maxheap with the points closest to qIndex*/
void pClosest(struct Tree* t, MaxHeap* H, int startIndex, int qIndex, int i);

#endif
