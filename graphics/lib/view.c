/**
 * Greg Attra
 * 10/13/2021
 * 
 * Implementation of the View2D and View3D API defined in view.h
 */

#include "view.h"
#include "matrix.h"
#include "point.h"
#include <math.h>

void matrix_setView2D(Matrix *vtm, View2D *v)
{
    double dy = (v->dx * ((double) v->screeny)) / ((double) v->screenx);
    double nx = v->x.val[0];
    double ny = v->x.val[1];

    matrix_identity(vtm);
    matrix_translate2D(vtm, -(v->vrp.val[0]), -(v->vrp.val[1]));
    matrix_rotateZ(vtm, nx, -ny);
    matrix_scale2D(vtm, ((double) v->screenx) / v->dx, -((double) v->screeny) / dy);
    matrix_translate2D(vtm, v->screenx / 2.0, v->screeny / 2.0);
}
