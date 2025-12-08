#ifndef POINT_H
#define POINT_H

/*Points in 3D storing x,y and z value*/

typedef struct {
    double x;
    double y;
    double z;
} Point;

/*returns the squared distance between two points (euclidian norm)*/
static inline float distSquared(Point p1, Point p2){

    return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z);
}

#endif
