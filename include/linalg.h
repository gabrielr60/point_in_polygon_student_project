#ifndef LINALG_H
#define LINALG_H
#include <gsl/gsl_matrix.h>
#include "kdtree.h"

Point* calc_centeroid(MaxHeap* H);

gsl_matrix* create_matrix(MaxHeap* H);

Point* find_normal(MaxHeap* H);






#endif