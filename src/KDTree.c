#include "/home/elias/cprojects/lidarCode/include/kdtree.h"

struct Node* initNode(float x, float y, float z, struct Node *p, struct Node *lc, struct Node *rc){
    
    struct Node *n = malloc(sizeof(struct Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed for Node\n");
        exit(EXIT_FAILURE);
    }
    n->x = x;
    n->y = y;
    n->z = z;
    n->parent = p;
    n->leftChild = lc;
    n->rightChild = rc;

    return n;
}

struct tree* initTree(){
    struct Tree* t = malloc(sizeof(struct Tree));
    if (!t) {
        fprintf(stderr, "Memory allocation failed for Node\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    t->nNodes = 0;
    return t;
}

void tree_insert(struct Tree* t, struct Node* n){
    struct Node* pos = t->root;
    if (pos == NULL){
        t->root = n;
        t->nNodes++;
        return;
    }
    struct Node* next = pos;
    int dir = 0;
    int i = 0;

    while (next != NULL){
        pos = next;
        if (i%3 == 0){
            if (pos->x > n->x){
                next = pos->leftChild;
                dir = -1;
            }
            else{
                next = pos->rightChild;
                dir = 1;
            }
        }
        else if (i%3 == 1){
            if (pos->y > n->y){
                next = pos->leftChild;
                dir = -1;
            }
            else{
                next = pos->rightChild;
                dir = 1;
            }
        }
        else{
            if (pos->z > n->z){
                next = pos->leftChild;
                dir = -1;
            }
            else{
                next = pos->rightChild;
                dir = 1;
            }
        }
        i++;
    }

    n->parent = pos;
    if (dir == -1){
        pos->leftChild = n;
    }
    if (dir == 1){
        pos->rightChild = n;
    }

    t->nNodes++;
    
    return;

}
