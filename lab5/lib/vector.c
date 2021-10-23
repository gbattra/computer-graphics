/**
 * Greg Attra
 * 10/12/2021
 * 
 * Implementation of the Vector API defined in vector.h
 */

#include "vector.h"
#include <math.h>

void vector_set(Vector *v, double x, double y, double z)
{
    v->val[0] = x;
    v->val[1] = y;
    v->val[2] = z;
}

void vector_print(Vector *v, FILE *fp)
{
    fprintf(fp, "x: %f, y: %f, z: %f\n", v->val[0], v->val[1], v->val[2]);
}

void vector_copy(Vector *to, Vector *from)
{
    to->val[0] = from->val[0];
    to->val[1] = from->val[1];
    to->val[2] = from->val[2];
}

double vector_length(Vector *v)
{
    double x = v->val[0];
    double y = v->val[1];
    double z = v->val[2];

    return sqrt((x*x) + (y*y) + (z*z));
}

void vector_normalize(Vector *v)
{
    double length = vector_length(v);
    v->val[0] = v->val[0] / length;
    v->val[1] = v->val[1] / length;
    v->val[2] = v->val[2] / length;
}

double vector_dot(Vector *a, Vector *b)
{
    double ax = a->val[0];
    double ay = a->val[1];
    double az = a->val[2];
    
    double bx = b->val[0];
    double by = b->val[1];
    double bz = b->val[2];

    return (ax*bx) + (ay*by) + (az*bz);
}

void vector_cross(Vector *a, Vector *b, Vector *c)
{
    double ax = a->val[0];
    double ay = a->val[1];
    double az = a->val[2];
    
    double bx = b->val[0];
    double by = b->val[1];
    double bz = b->val[2];

    double cx = (ay*bz) - (az*by);
    double cy = (az*bx) - (ax*bz);
    double cz = (ax*by) - (ay*bx);

    c->val[0] = cx;
    c->val[1] = cy;
    c->val[2] = cz;
}
