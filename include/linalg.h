#ifndef LINALG_H
#define LINALG_H
#include <gsl/gsl_matrix.h>
#include "kdtree.h"

Point* calc_centeroid(struct Tree* t, MaxHeap* H);

gsl_matrix* create_matrix(struct Tree* t, MaxHeap* H);

Point* find_normal(struct Tree* t, MaxHeap* H);

#endif






#endif
