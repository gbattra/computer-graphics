/**
 * Greg Attra
 * 10/13/2021
 * 
 * Implementation of the View2D and View3D API defined in view.h
 */

#include "view.h"
#include "matrix.h"
#include "vector.h"
#include "point.h"
#include <math.h>

void view2D_set(View2D *view, Point *vrp, double dx, Vector *x, int screenx, int screeny)
{
    point_copy(&view->vrp, vrp);
    vector_copy(&view->x, x);
    view->dx = dx;
    view->screenx = screenx;
    view->screeny = screeny;
}

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

void matrix_setView3D(Matrix *vtm, View3D *v)
{
    Vector u;
    vector_cross(&v->vup, &v->vpn, &u);
    vector_cross(&v->vpn, &u, &v->vup);
    
    matrix_identity(vtm);
    matrix_translate(vtm, -(v->vrp.val[0]), -(v->vrp.val[1]), -(v->vrp.val[2]));

    vector_normalize(&u);
    vector_normalize(&v->vup);
    vector_normalize(&v->vpn);

    matrix_rotateXYZ(vtm, &u, &v->vup, &v->vpn);
    matrix_translate(vtm, 0, 0, v->d);

    double bp = v->d + v->b;
    matrix_scale(vtm, (2.0*v->d) / (bp*v->du), (2.0*v->d) / (bp*v->dv), 1.0 / bp);
    
    double dp = v->d / bp;
    matrix_perspective(vtm, dp);
    matrix_scale2D(vtm, -(v->screenx / (2.0*dp)), -(v->screeny / (2.0*dp)));
    matrix_translate2D(vtm, v->screenx / 2.0, v->screeny / 2.0);
}
