/**
 * Greg Attra
 * 11/07/2021
 * 
 * Implementation of Bezier curve API defined in bezier.h
 */

#include "matrix.h"
#include "curve.h"
#include "point.h"
#include "list.h"
#include <math.h>


void bezierCurve_init(BezierCurve *bc)
{
    bc->zBuffer = 1;

    float val = 0.0;
    float delim = 1.0/4.0;

    for (int i = 0; i < 4; i++)
    {
        // point_set3D(&bc->vlist[i], val, 0, 0);
        val += delim;
    }
}

void bezierSurface_init(BezierSurface *bs)
{
    bs->zBuffer = 1;
    
    float xVal = 0.0;
    float delim = 1.0/4.0;
    for (int i = 0; i < 4; i++)
    {
        float zVal = 0.0;
        for (int j = 0; j < 4; j++)
        {
            point_set3D(&bs->vlist[(i * 4) + j], xVal, 0, zVal);
            zVal += delim;
        }
        xVal += delim;
    }
}

void bezierCurve_set(BezierCurve *bc, Point *vlist)
{
    for (int i = 0; i < 4; i++)
    {
        point_copy(&bc->vlist[i], &vlist[i]);
    }
}

void bezierSurface_set(BezierSurface *bs, Point *vlist)
{
    for (int i = 0; i < 16; i++)
    {
        point_copy(&bs->vlist[i], &vlist[i]);
    }
}

void bezierCurve_zBuffer(BezierCurve *bc, int flag)
{
    bc->zBuffer = flag;
}

void bezierSurface_zBuffer(BezierSurface *bs, int flag)
{
    bs->zBuffer = flag;
}

void bezierCurve_copy(BezierCurve *to, BezierCurve *from)
{
    to->zBuffer = from->zBuffer;
    bezierCurve_set(to, from->vlist);
}

void bezierCurve_normalize(BezierCurve *bc)
{
    for (int i = 0; i < 4; i++)
    {
        point_normalize(&bc->vlist[i]);
    }
}

void bezierSurface_copy(BezierSurface *to, BezierSurface *from)
{
    to->zBuffer = from->zBuffer;
    bezierSurface_set(to, from->vlist);
}

/**
 * Compare two bezier curves.
 * 
 * @param one the first curve
 * @param two the second curve
 * 
 * @return -1 if one < two, 0 if equal, 1 if two < one
 */
static int bezierCurve_compare(const void *one, const void *two)
{
    BezierCurve *bc_one = (BezierCurve *) one;
    BezierCurve *bc_two = (BezierCurve *) two;

    if (bc_one->vlist[0].val[0] < bc_two->vlist[0].val[0])
    {
        return -1;
    }
    if (bc_one->vlist[0].val[0] > bc_two->vlist[0].val[0])
    {
        return 1;
    }
    return 0;
}

/**
 * Compare two bezier surfaces.
 * 
 * @param one the first surface
 * @param two the second surface
 * 
 * @return -1 if one < two, 0 if equal, 1 if one > two
 */
static int bezierSurface_compare(const void *one, const void *two)
{
    BezierSurface *bc_one = (BezierSurface *) one;
    BezierSurface *bc_two = (BezierSurface *) two;

    if (bc_one->vlist[0].val[0] < bc_two->vlist[0].val[0])
    {
        return -1;
    }
    if (bc_one->vlist[0].val[0] > bc_two->vlist[0].val[0])
    {
        return 1;
    }
    return 0;
}

void bezier_divideControlPoints(Point *points, Point *left, Point *right)
{
    Point plist[4];
    point_copyList(plist, points, 4);
    int r = 0;
    while (r < 3)
    {
        point_copy(&left[r], &plist[0]);
        point_copy(&right[3-r], &plist[3-r]);
        Point tmp_plist[3-r];
        for (int i = 0; i < 3 - r; i++)
        {
            Point *start = &plist[i];
            Point *end = &plist[i + 1];
            float x = (start->val[0] + end->val[0]) / 2.0;
            float y = (start->val[1] + end->val[1]) / 2.0;
            float z = (start->val[2] + end->val[2]) / 2.0;

            Point midpoint;
            point_set3D(&midpoint, x, y, z);
            point_copy(&tmp_plist[i], &midpoint);
        }
        point_copyList(plist, tmp_plist, 3 - r);
        r += 1;
    }

    point_copy(&left[3], &plist[0]);
    point_copy(&right[0], &plist[0]);
}

void bezierCurve_divide(
    BezierCurve *bc,
    LinkedList *curves,
    int n_divs)
{
    if (n_divs <= 0)
    {
        BezierCurve *curve = (BezierCurve *) malloc(sizeof(BezierCurve));
        bezierCurve_copy(curve, bc);
        ll_insert(curves, curve, &bezierCurve_compare);
        return;
    }

    BezierCurve left;
    BezierCurve right;
    bezierCurve_init(&left);
    bezierCurve_init(&right);

    bezier_divideControlPoints(bc->vlist, left.vlist, right.vlist);

    int divs_remaining = n_divs - 1;
    bezierCurve_divide(&left, curves, divs_remaining);
    bezierCurve_divide(&right, curves, divs_remaining);

    return;
}

void bezierSurface_divide(
    BezierSurface *bs,
    LinkedList *surfaces,
    int n_divs)
{
    if (n_divs <= 0)
    {
        BezierSurface *surface = (BezierSurface *) malloc(sizeof(BezierSurface));
        bezierSurface_copy(surface, bs);
        ll_insert(surfaces, surface, &bezierSurface_compare);
        return;
    }

    BezierSurface left;
    BezierSurface right;
    bezierSurface_init(&left);
    bezierSurface_init(&right);

    for (int i = 0; i < 4; i++)
    {
        bezier_divideControlPoints(&bs->vlist[i * 4], &left.vlist[i * 4], &right.vlist[i * 4]);
    }
    
    int divs_remaining = n_divs - 1;
    bezierSurface_divide(&left, surfaces, divs_remaining);
    bezierSurface_divide(&right, surfaces, divs_remaining);

    return;
}

void bezierCurve_draw(BezierCurve *bc, Image *src, Color c)
{   
    int n_divs = ((float) src->rows / (float) src->cols) * 10.0;
    LinkedList *curves = ll_new();
    bezierCurve_divide(bc, curves, n_divs);

    BezierCurve *curr = (BezierCurve *) ll_pop(curves);
    while (curr)
    {
        for (int i = 0; i < 3; i++)
        {
            Line l;
            line_set2D(
                &l,
                curr->vlist[i].val[0],
                curr->vlist[i].val[1],
                curr->vlist[i+1].val[0],
                curr->vlist[i+1].val[1]);
            line_draw(&l, src, c);
        }
        free(curr);
        curr = ll_pop(curves);
    }
}