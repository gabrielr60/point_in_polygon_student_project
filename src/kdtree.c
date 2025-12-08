#include "kdtree.h"

/*Initialize KD-tree*/
struct Tree* initTree(int capacity) {
    struct Tree* t = malloc(sizeof(struct Tree));
    t->data = malloc(sizeof(struct Node) * capacity);
    t->capacity = capacity;
    t->nNodes = 0;

    //No children at initilization
    for (int i = 0; i < capacity; i++) {
        t->data[i].leftChildIndex = -1;
        t->data[i].rightChildIndex = -1;
    }

    return t;
}

/*Insert new point in tree*/
void tree_insert(struct Tree* t, int newPointIndex){
    int pos = 0; //start at root
    int run = 1; //continue down tree until leaf found
    int axes = 0; //keeps track och axes 
    int dir = 0; //1 = go to right child, -1 = go to left

    while(run){
        //Go left/right based on if on what side of the splitting plane 
        if(axes==0){
            if(t->data[pos].coords.x > t->data[newPointIndex].coords.x){
                dir = -1;
            }
            else{
                dir = 1;
            }
        }
        if(axes==1){
            if(t->data[pos].coords.y > t->data[newPointIndex].coords.y){
                dir = -1;
            }
            else{
                dir = 1;
            }
        }
        if(axes==2){
            if(t->data[pos].coords.z > t->data[newPointIndex].coords.z){
                dir = -1;
            }
            else{
                dir = 1;
            }
        }

        //Go to left/right, update position or place new index if child leaf
        if(dir == -1){
            if(t->data[pos].leftChildIndex != -1){
                pos = t->data[pos].leftChildIndex;
            }
            else{
                t->data[pos].leftChildIndex = newPointIndex;
                run = 0;
            }
        }
        else{
            if(t->data[pos].rightChildIndex != -1){
                pos = t->data[pos].rightChildIndex;
            }
            else{
                t->data[pos].rightChildIndex = newPointIndex;
                run = 0;
            }
        }
        axes = (axes+1)%3; //change axes of comparisson
    }

    t->nNodes++; //increase number of nodes in tree

}

/*Fill maxheap with points closest to point q in tree*/
void pClosest(struct Tree* t, MaxHeap* H, int nodeIndex, int qIndex, int i){

    //if subtree empty, dont look for candidates
    if (nodeIndex == -1)
        return;

    float d = distSquared(t->data[nodeIndex].coords, t->data[qIndex].coords); //calculate distance from nodepoint to q

    //insert in nodepoint if heap not full or if closer then current contenders
    if (H->size < H->capacity) {
        heap_insert(H, d, nodeIndex);
    } else if (d < H->data[0].dist) {
        heap_insert(H, d, nodeIndex);
    }

    float diff;
    if (i == 0)
        diff = t->data[qIndex].coords.x - t->data[nodeIndex].coords.x;
    else if (i == 1)
        diff = t->data[qIndex].coords.y - t->data[nodeIndex].coords.y;
    else
        diff = t->data[qIndex].coords.z - t->data[nodeIndex].coords.z;

    int nearChild  = (diff < 0 ? t->data[nodeIndex].leftChildIndex  : t->data[nodeIndex].rightChildIndex);
    int farChild   = (diff >= 0 ? t->data[nodeIndex].leftChildIndex  : t->data[nodeIndex].rightChildIndex);

    pClosest(t, H, nearChild, qIndex, (i + 1) % 3);

    float diff2 = diff * diff;

    if (H->size < H->capacity || diff2 < H->data[0].dist) {
        pClosest(t, H, farChild, qIndex, (i + 1) % 3);
    }
}
