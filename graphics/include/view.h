/**
 * Greg Attra
 * 10/13/2021
 * 
 * Header for defining the View2D and View3D structs and API.
 */

#ifndef VIEW
#define VIEW

#include "matrix.h"
#include "vector.h"

typedef struct
{
    Point vrp;
    double dx;
    Vector x;
    int screenx;
    int screeny;
} View2D;

/**
 * Transforms VTM by the specified View2D struct.
 * 
 * @param vtm the matrix to transform
 * @param v the view to transform the matrix with
 * 
 * @return void
 */
void matrix_setView2D(Matrix *vtm, View2D *v);

#endif
