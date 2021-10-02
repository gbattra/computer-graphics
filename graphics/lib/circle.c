/**
 * Greg Attra
 * 09/30/2021
 * 
 * Implementation of the API defined in Circle.h
 */

#include "circle.h"
#include "point.h"
#include "image.h"
#include "stdlib.h"
#include <math.h>

#define MAX_ITER 10000


void circle_set(Circle *circle, Point tp, double tr)
{
    circle->center = tp;
    circle->radius = tr;
}

static void set_pixel(int x, int y, Image *src, FPixel pix)
{
    Point p;
    p.val[0] = x;
    p.val[1] = y;
    point_draw(&p, src, pix);
}

static void reflect_eight(int xc, int yc, int dx, int dy, FPixel pix, Image *src)
{
    set_pixel(xc + dx, yc + dy, src, pix);
    set_pixel(xc - dx, yc + dy, src, pix);
    set_pixel(xc + dx, yc - dy, src, pix);
    set_pixel(xc - dx, yc - dy, src, pix);

    set_pixel(xc + dy, yc + dx, src, pix);
    set_pixel(xc - dy, yc + dx, src, pix);
    set_pixel(xc + dy, yc - dx, src, pix);
    set_pixel(xc - dy, yc - dx, src, pix);
}

// Implementatin inspired by circleMidpoint.c
void circle_draw(Circle *circle, Image *src, Color c)
{
    FPixel pix;
    pix.rgb[0] = c.c[0];
    pix.rgb[1] = c.c[1];
    pix.rgb[2] = c.c[2];

    double r = circle->radius;
    int xc = circle->center.val[0];
    int yc = circle->center.val[1];
    int dx = 0;
    int dy = r;
    int e = 1 - r;
    reflect_eight(xc, yc, dx, dy, pix, src);

    while (dx < dy)
    {
        dx++;
        if (e < 0)
        {
            e += 2 * dx + 1;
        }
        else
        {
            dy--;
            e += 2 * (dx - dy) + 1;
        }
        reflect_eight(xc, yc, dx, dy, pix, src);
    }
}
