/**
 * Greg Attra
 * 11/10/2021
 * 
 * Implementation of the Cone.h api.
 */

#include "cone.h"
#include "matrix.h"
#include <math.h>

Cone *cone_create(Point *cp, float r, float h)
{
    Cone *cone = (Cone *) malloc(sizeof(Cone));
    point_copy(&cone->cp, cp);
    cone->r = r;
    cone->h = h;

    float angle = (2.0*M_PI) / 3.0;

    Point corners[3];
    for (int i = 0; i < 3; i++)
    {
        Point point;
        point_set3D(&point, r, 0, 0);
        Matrix m;
        matrix_identity(&m);
        matrix_rotateY(&m, cos(((float) i) * angle), sin(((float) i) * angle));
        matrix_xformPoint(&m, &point, &corners[i]);
    }

    cone->base = polygon_createp(3, corners);

    Point top;
    point_set3D(&top, cp->val[0], cp->val[1] + h, cp->val[2]);
    cone->faces = (Triangle *) malloc(sizeof(Triangle) * 3);
    for (int i = 0; i < 3; i++)
    {
        int i_next = i+1;
        if (i == 2) i_next = 0;

        Point vlist[3];
        point_copy(&vlist[0], &top);
        point_copy(&vlist[1], &corners[i]);
        point_copy(&vlist[2], &corners[i_next]);

        polygon_set(&cone->faces[i], 3, vlist);
    }

    return cone;
}


void cone_divide(Cone *cone, int n_divs);