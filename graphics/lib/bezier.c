/**
 * Greg Attra
 * 11/07/2021
 * 
 * Implementation of Bezier curve API defined in bezier.h
 */

#include "bezier.h"


void bezierCurve_init(BezierCurve *bc)
{
    bc->zBuffer = 1;

    float val = 0.0;
    float delim = 1.0/4.0;
    for (int i = 0; i < 4; i++)
    {
        point_set3D(&bc->vlist[i], val, 0, 0);
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
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            point_copy(&bs->vlist[(i * 4) + j], &vlist[(i * 4) + j]);
        }
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

void bezierCurve_draw(BezierSurface *bc, Image *src, Color c)
{
    
}

