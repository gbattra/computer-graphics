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
#include "line.h"
#include <math.h>

#define MAX_ITER 10000


void circle_set(Circle *circle, Point tp, double tr)
{
    circle->center = tp;
    circle->radius = tr;
}

/**
 * Sets the point on the image given x and y in Cartesian coords.
 * 
 * @param x the x coord
 * @param y the y coord
 * @param src the image to draw on
 * @param pix the pixel to draw
 * 
 * @return void
 */
static void set_pixel(int x, int y, Image *src, FPixel pix)
{
    Point p;
    p.val[0] = x;
    p.val[1] = y;
    point_draw(&p, src, pix);
}

/**
 * Reflects a dx and dy from a given center point around the eight axis of symmetry.
 * 
 * @param xc the center x coord
 * @param yc the center y coord
 * @param dx the delta in x
 * @param dy the delta in y
 * @param c the color value to set
 * @param src the image to update
 * 
 * @return void
 */
static void reflect_eight(int xc, int yc, int dx, int dy, Color c, Image *src)
{
    FPixel pix;
    pix.rgb[0] = c.c[0];
    pix.rgb[1] = c.c[1];
    pix.rgb[2] = c.c[2];

    set_pixel(xc + dx, yc + dy, src, pix);
    set_pixel(xc - dx, yc + dy, src, pix);
    set_pixel(xc + dx, yc - dy, src, pix);
    set_pixel(xc - dx, yc - dy, src, pix);

    set_pixel(xc + dy, yc + dx, src, pix);
    set_pixel(xc - dy, yc + dx, src, pix);
    set_pixel(xc + dy, yc - dx, src, pix);
    set_pixel(xc - dy, yc - dx, src, pix);
}

/**
 * Fill the row given the start and endpoint.
 * 
 * @param x0 the start x
 * @param y0 the start y
 * @param x1 the end x
 * @param y1 the end y
 * @param c the color to draw
 * @param src the image to draw on
 * 
 * @return void
 */
static void fill_row(int x0, int y0, int x1, int y1, Color c, Image *src)
{
    Line l;
    l.a.val[0] = x0;
    l.a.val[1] = y1;
    l.b.val[0] = x1;
    l.b.val[1] = y1;

    line_draw(&l, src, c);
}

/**
 * Fill the rows in the circle.
 * 
 * @param xc the center x
 * @param yc the center y
 * @param dx the delta in x
 * @param dy the delta in y
 * @param c the color to draw
 * @param src the image to draw on
 * 
 * @return void
 */
static void fill_rows(int xc, int yc, int dx, int dy, Color c, Image *src)
{
    fill_row(xc - dx, yc + dy, xc + dx, yc + dy, c, src);
    fill_row(xc - dx, yc - dy, xc + dx, yc - dy, c, src);
    fill_row(xc - dy, yc - dx, xc + dy, yc - dx, c, src);
    fill_row(xc - dy, yc + dx, xc + dy, yc + dx, c, src);
}

/**
 * Implementatin of drawing the circle with optional fill param.
 * 
 * @param cl the circle to draw
 * @param src the image to draw on
 * @param c the color of the circle
 * @param fill flag to indicate if circle should be filled
 * 
 * @return void
 */
static void draw_circle(Circle *cl, Image *src, Color c, int fill)
{
    double r = cl->radius;
    int xc = cl->center.val[0];
    int yc = cl->center.val[1];
    int dx = 0;
    int dy = r;
    int e = 1 - r;
    reflect_eight(xc, yc, dx, dy, c, src);

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
        reflect_eight(xc, yc, dx, dy, c, src);
        if (fill) fill_rows(xc, yc, dx, dy, c, src);
    }

    if (fill) fill_row(xc - r, yc, xc + r, yc, c, src);
}

// Implementatin inspired by circleMidpoint.c
void circle_draw(Circle *cl, Image *src, Color c)
{
    draw_circle(cl, src, c, 0);
}

void circle_drawFill(Circle *cl, Image *src, Color c)
{
    draw_circle(cl, src, c, 1);
}
