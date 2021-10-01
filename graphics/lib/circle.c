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

static void reflect_eight(int xc, int yc, int dx, int dy, FPixel pix, Image *src)
{
    Point p;
    p.val[0] = xc + dx;
    p.val[1] = yc + dy;
    point_draw(&p, src, pix);

    // p.val[0] = xc + dx;
    // p.val[1] = yc - dy;
    // point_draw(&p, src, pix);

    // p.val[0] = xc - dx;
    // p.val[1] = yc + dy;
    // point_draw(&p, src, pix);

    // p.val[0] = xc - dx;
    // p.val[1] = yc - dy;
    // point_draw(&p, src, pix);

    // p.val[0] = xc + dy;
    // p.val[1] = yc + dx;
    // point_draw(&p, src, pix);

    // p.val[0] = xc + dy;
    // p.val[1] = yc - dx;
    // point_draw(&p, src, pix);

    // p.val[0] = xc - dy;
    // p.val[1] = yc + dx;
    // point_draw(&p, src, pix);

    // p.val[0] = xc - dy;
    // p.val[1] = yc - dx;
    // point_draw(&p, src, pix);
}

void circle_draw(Circle *circle, Image *src, Color c)
{
    double r = circle->radius;
    int xc = circle->center.val[0];
    int yc = circle->center.val[1];
    int x0 = xc;
    int y0 = yc + r;
    double m = 0;
    int i = 0;
    while (m < 1 || i < MAX_ITER)
    {
        int x1 = x0 + 1;
        int y1 = yc + sqrtf(((r*r) - ((xc - x1)*(xc-x1))));
        printf("x: %i , y: %i\n", x1, y1);
        m = abs((y1 - y0)) / abs((x1 - x0));

        // FPixel pix;
        // pix.rgb[0] = c.c[0];
        // pix.rgb[1] = c.c[1];
        // pix.rgb[2] = c.c[2];

        // int dx = x1 - xc;
        // int dy = y1 - yc;
        // reflect_eight(xc, yc, dx, dy, pix, src);
        
        y0 = y1;
        x0 = x1;
        i++;
    }
}
