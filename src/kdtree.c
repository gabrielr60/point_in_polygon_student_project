#include "kdtree.h"

struct Node* initNode(Point* coords, struct Node *p, struct Node *lc, struct Node *rc){
    
    struct Node *n = malloc(sizeof(struct Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed for Node\n");
        exit(EXIT_FAILURE);
    }
    n->coords = coords;
    n->parent = p;
    n->leftChild = lc;
    n->rightChild = rc;

    return n;
}

struct Tree* initTree(){
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
            if (pos->coords->x > n->coords->x){
                next = pos->leftChild;
                dir = -1;
            }
            else{
                next = pos->rightChild;
                dir = 1;
            }
        }
        else if (i%3 == 1){
            if (pos->coords->y > n->coords->y){
                next = pos->leftChild;
                dir = -1;
            }
            else{
                next = pos->rightChild;
                dir = 1;
            }
        }
        else{
            if (pos->coords->z > n->coords->z){
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

/*

void pClosest(MaxHeap* closest, struct Node* start, Point *q, int i){

    if (start == NULL){
        return;
    }

    float d = distSquared(q, start->coords);

    if(closest->size < closest->capacity){
        heap_insert(closest, d, start->coords);
    }

    else if(d < closest->data[0].dist){
        heap_insert(closest, d, start->coords);
    }

    if (i==0){

        if (q->x < start->coords->x){
            
            pClosest(closest, start->leftChild, q, (i+1)%3);

            if ((q->x - start->coords->x)*(q->x - start->coords->x) < closest->data[0].dist){
                pClosest(closest, start->rightChild, q, (i+1)%3);
            }

        }

        else{

            pClosest(closest, start->rightChild, q, (i+1)%3);

            if ((q->x - start->coords->x)*(q->x - start->coords->x) < closest->data[0].dist){
                pClosest(closest, start->leftChild, q, (i+1)%3);
            }

        }

    }

    if (i==1){

        if (q->y < start->coords->y){
            
            pClosest(closest, start->leftChild, q, (i+1)%3);

            if ((q->y - start->coords->y)*(q->y - start->coords->y) < closest->data[0].dist){
                pClosest(closest, start->rightChild, q, (i+1)%3);
            }

        }

        else{

            pClosest(closest, start->rightChild, q, (i+1)%3);

            if ((q->y - start->coords->y)*(q->y - start->coords->y) < closest->data[0].dist){
                pClosest(closest, start->leftChild, q, (i+1)%3);
            }

        }

    }

    if (i==2){

        if (q->z < start->coords->z){
            
            pClosest(closest, start->leftChild, q, (i+1)%3);

            if ((q->z - start->coords->z)*(q->z - start->coords->z) < closest->data[0].dist){
                pClosest(closest, start->rightChild, q, (i+1)%3);
            }

        }

        else{

            pClosest(closest, start->rightChild, q, (i+1)%3);

            if ((q->z - start->coords->z)*(q->z - start->coords->z) < closest->data[0].dist){
                pClosest(closest, start->leftChild, q, (i+1)%3);
            }

        }

    }

}

*/

void pClosest(MaxHeap* H, struct Node* node, Point *q, int axis) {
    if (node == NULL)
        return;

    float d = distSquared(q, node->coords);

    if (H->size < H->capacity) {
        heap_insert(H, d, node->coords);
    } else if (d < H->data[0].dist) {
        heap_insert(H, d, node->coords);
    }

    float diff;
    if (axis == 0)
        diff = q->x - node->coords->x;
    else if (axis == 1)
        diff = q->y - node->coords->y;
    else
        diff = q->z - node->coords->z;

    struct Node* nearChild  = (diff < 0 ? node->leftChild  : node->rightChild);
    struct Node* farChild   = (diff < 0 ? node->rightChild : node->leftChild);

    pClosest(H, nearChild, q, (axis + 1) % 3);

    float diff2 = diff * diff;

    if (H->size < H->capacity || diff2 < H->data[0].dist) {
        pClosest(H, farChild, q, (axis + 1) % 3);
    }
}
