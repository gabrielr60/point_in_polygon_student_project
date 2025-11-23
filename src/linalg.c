#include "linalg.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h> 
#include <math.h>

Point* calc_centeroid(MaxHeap* H){

    Point* cent = malloc(sizeof(Point));
    cent->x = 0;
    cent->y = 0;
    cent->z = 0;

    for(int i = 0; i < H->capacity; i++){

        cent->x += H->data[i].pt->x;
        cent->y += H->data[i].pt->y;
        cent->z += H->data[i].pt->z;

    }

    cent->x = cent->x/H->capacity;
    cent->y = cent->y/H->capacity;
    cent->z = cent->z/H->capacity;

    return cent;

}

gsl_matrix* create_matrix(MaxHeap* H){

    Point* cent = calc_centeroid(H);

    gsl_matrix *C = gsl_matrix_calloc(3, 3);

    for (int i = 0; i < H->capacity; i++){

        double dx = H->data[i].pt->x - cent->x;
        double dy = H->data[i].pt->y - cent->y;
        double dz = H->data[i].pt->z - cent->z;

        gsl_matrix_set(C, 0, 0, gsl_matrix_get(C, 0, 0) + dx*dx);
        gsl_matrix_set(C, 0, 1, gsl_matrix_get(C, 0, 1) + dx*dy);
        gsl_matrix_set(C, 0, 2, gsl_matrix_get(C, 0, 2) + dx*dz);

        gsl_matrix_set(C, 1, 0, gsl_matrix_get(C, 1, 0) + dy*dx);
        gsl_matrix_set(C, 1, 1, gsl_matrix_get(C, 1, 1) + dy*dy);
        gsl_matrix_set(C, 1, 2, gsl_matrix_get(C, 1, 2) + dy*dz);

        gsl_matrix_set(C, 2, 0, gsl_matrix_get(C, 2, 0) + dz*dx);
        gsl_matrix_set(C, 2, 1, gsl_matrix_get(C, 2, 1) + dz*dy);
        gsl_matrix_set(C, 2, 2, gsl_matrix_get(C, 2, 2) + dz*dz);

    }

    gsl_matrix_set(C, 0, 0, gsl_matrix_get(C, 0, 0)/H->capacity);
    gsl_matrix_set(C, 0, 1, gsl_matrix_get(C, 0, 1)/H->capacity);
    gsl_matrix_set(C, 0, 2, gsl_matrix_get(C, 0, 2)/H->capacity);

    gsl_matrix_set(C, 1, 0, gsl_matrix_get(C, 1, 0)/H->capacity);
    gsl_matrix_set(C, 1, 1, gsl_matrix_get(C, 1, 1)/H->capacity);
    gsl_matrix_set(C, 1, 2, gsl_matrix_get(C, 1, 2)/H->capacity);

    gsl_matrix_set(C, 2, 0, gsl_matrix_get(C, 2, 0)/H->capacity);
    gsl_matrix_set(C, 2, 1, gsl_matrix_get(C, 2, 1)/H->capacity);
    gsl_matrix_set(C, 2, 2, gsl_matrix_get(C, 2, 2)/H->capacity);

    return C;
}

Point* find_normal(MaxHeap* H){

    gsl_matrix* C = create_matrix(H);

    gsl_vector *eval = gsl_vector_alloc(3);
    gsl_matrix *evec = gsl_matrix_alloc(3,3);

    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(3);

    gsl_eigen_symmv(C, eval, evec, w);
    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_ASC);

    double nx = gsl_matrix_get(evec, 0, 0);
    double ny = gsl_matrix_get(evec, 1, 0);
    double nz = gsl_matrix_get(evec, 2, 0);

    double d = sqrt(nx*nx + ny*ny + nz*nz);

    Point* n = malloc(sizeof(Point));
    n->x = nx/d;
    n->y = ny/d;
    n->z = nz/d;

    return n;

}


