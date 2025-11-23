#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
#include "heap.h"
#include "linalg.h"
#include <math.h>
#include"las_reader.h"


int main() {
	
    struct LASFile* las_file = malloc(sizeof(struct LASFile));

    int npoints = 1000;
    initLASFile(las_file, "../data/2631_1113.las", npoints);

    struct Tree* T = initTree();

    for (int i = 0; i < npoints ; i++){

        struct Node* newNode = initNode(&las_file->pts[i], NULL, NULL, NULL);
        tree_insert(T, newNode);

    }

    Point* normals = malloc(sizeof(Point)*npoints);

    for (int i = 0; i < npoints; i++){

        MaxHeap* H = heap_create(7);
        pClosest(H, T->root, &las_file->pts[i], 0);
        normals[i] = *find_normal(H);

    }

    double scale = 1; // längden på normala vektorer i plotten
    FILE *f = fopen("../data/normals.dat", "w");
    if (!f) {
        perror("Could not open file");
        return 1;
    }

    for (int i = 0; i < npoints; i++) {
	
        double x0 = las_file->pts[i].x;
        double y0 = las_file->pts[i].y;
        double z0 = las_file->pts[i].z;

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
