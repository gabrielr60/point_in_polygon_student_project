#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
#include "heap.h"
#include "linalg.h"
#include <math.h>

int main() {

    Point points[100] = {
    {0,0,0.0}, {1,0,0.12}, {2,0,0.43}, {3,0,0.86}, {4,0,1.55}, {5,0,2.53}, {6,0,3.63}, {7,0,4.75}, {8,0,6.05}, {9,0,8.12},
    {0,1,0.11}, {1,1,0.35}, {2,1,0.68}, {3,1,1.03}, {4,1,1.78}, {5,1,2.62}, {6,1,3.65}, {7,1,4.88}, {8,1,6.13}, {9,1,8.05},
    {0,2,0.38}, {1,2,0.58}, {2,2,1.01}, {3,2,1.57}, {4,2,2.34}, {5,2,3.17}, {6,2,4.18}, {7,2,5.31}, {8,2,6.58}, {9,2,8.22},
    {0,3,0.87}, {1,3,1.08}, {2,3,1.52}, {3,3,2.14}, {4,3,3.05}, {5,3,3.95}, {6,3,5.04}, {7,3,6.32}, {8,3,7.64}, {9,3,9.12},
    {0,4,1.52}, {1,4,1.82}, {2,4,2.34}, {3,4,3.04}, {4,4,4.03}, {5,4,4.98}, {6,4,6.13}, {7,4,7.47}, {8,4,8.92}, {9,4,10.48},
    {0,5,2.33}, {1,5,2.58}, {2,5,3.11}, {3,5,3.82}, {4,5,4.79}, {5,5,5.92}, {6,5,7.17}, {7,5,8.63}, {8,5,10.23}, {9,5,11.95},
    {0,6,3.29}, {1,6,3.62}, {2,6,4.18}, {3,6,4.92}, {4,6,5.88}, {5,6,7.00}, {6,6,8.33}, {7,6,9.82}, {8,6,11.50}, {9,6,13.28},
    {0,7,4.40}, {1,7,4.72}, {2,7,5.28}, {3,7,6.02}, {4,7,7.03}, {5,7,8.21}, {6,7,9.58}, {7,7,11.12}, {8,7,12.85}, {9,7,14.72},
    {0,8,5.66}, {1,8,6.02}, {2,8,6.55}, {3,8,7.34}, {4,8,8.33}, {5,8,9.47}, {6,8,10.78}, {7,8,12.28}, {8,8,14.00}, {9,8,15.92},
    {0,9,7.07}, {1,9,7.52}, {2,9,8.12}, {3,9,9.02}, {4,9,10.12}, {5,9,11.35}, {6,9,12.78}, {7,9,14.38}, {8,9,16.20}, {9,9,18.20}
    };

    struct Tree* T = initTree();

    for (int i = 0; i < 100; i++){

        struct Node* newNode = initNode(&points[i], NULL, NULL, NULL);
        tree_insert(T, newNode);

    }

    Point* normals = malloc(sizeof(Point)*100);

    for (int i = 0; i < 100; i++){

        MaxHeap* H = heap_create(7);
        pClosest(H, T->root, &points[i], 0);
        normals[i] = *find_normal(H);

    }

    double scale = 1; // längden på normala vektorer i plotten
    FILE *f = fopen("normals.dat", "w");
    if (!f) {
        perror("Could not open file");
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        double x0 = points[i].x;
        double y0 = points[i].y;
        double z0 = points[i].z;

        // Kolumner 4-6 = vektorkomponenter, inte slutpunkt
        double dx = scale * normals[i].x;
        double dy = scale * normals[i].y;
        double dz = scale * normals[i].z;

        fprintf(f, "%f %f %f %f %f %f\n", x0, y0, z0, dx, dy, dz);
    }

    fclose(f);

    printf("Normals data written to normals.dat\n");
    return 0;
    
}
