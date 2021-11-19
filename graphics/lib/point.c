/**
 * Greg Attra
 * 09/30/2021
 * 
 * Implementation of the functions defined in point.h
 */

#include "point.h"
#include "image.h"
#include <stdio.h>
#include <math.h>

void point_set2D(Point *p, double x, double y)
{
    p->val[0] = x;
    p->val[1] = y;
    p->val[2] = 0.0;
    p->val[3] = 1.0;
}

void point_set3D(Point *p, double x, double y, double z)
{
    p->val[0] = x;
    p->val[1] = y;
    p->val[2] = z;
    p->val[3] = 1.0;
}

void point_set(Point *p, double x, double y, double z, double h)
{
    p->val[0] = x;
    p->val[1] = y;
    p->val[2] = z;
    p->val[3] = h;
}

void point_normalize(Point *p)
{
    p->val[0] = p->val[0] / p->val[3];
    p->val[1] = p->val[1] / p->val[3];
    p->val[3] = p->val[3] / p->val[3];
}

void point_normalize_z(Point *p)
{
    p->val[0] = p->val[0] / p->val[3];
    p->val[1] = p->val[1] / p->val[3];
    p->val[2] = p->val[2] / p->val[3];
    p->val[3] = p->val[3] / p->val[3];
}

void point_copy(Point *to, Point *from)
{
    to->val[0] = from->val[0];
    to->val[1] = from->val[1];
    to->val[2] = from->val[2];
    to->val[3] = from->val[3];
}

void point_draw(Point *p, Image *src, FPixel c)
{
    if (p->val[0] < 0 || p->val[0] > src->cols
    || p->val[1] < 0 || p->val[1] > src->rows - 1) return;

    image_setf(src, (int) p->val[1], (int) p->val[0], c);
}

void point_print(Point *p, FILE *fp)
{
    fprintf(fp, "(%f, %f, %f) | h: %f\n", p->val[0], p->val[1], p->val[2], p->val[3]);
}

void point_copyList(Point *to_plist, Point *from_plist, int n_points)
{
    for (int i = 0; i < n_points; i++)
    {
        point_copy(&to_plist[i], &from_plist[i]);
    }
}

void point_project(Point *p, Point *cp, float d, Point *dst)
{

    Point tmp;
    point_set3D(
        &tmp,
        p->val[0] - cp->val[0],
        p->val[1] - cp->val[1],
        p->val[2] - cp->val[2]);
    
    float mag = sqrtf((tmp.val[0]*tmp.val[0]) + (tmp.val[1]*tmp.val[1]) + (tmp.val[2]*tmp.val[2]));
    tmp.val[3] = mag;
    point_normalize_z(&tmp);

    point_set3D(
        &tmp,
        tmp.val[0] * d,
        tmp.val[1] * d,
        tmp.val[2] * d);

    point_copy(dst, &tmp);
}