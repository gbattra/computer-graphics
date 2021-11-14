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

/**
 * Sets the point on the image given x and y in Cartesian coords.
 * 
 * @param x the x coord
 * @param y the y coord
 * @param circ the circle being drawn
 * @param ca the start color
 * @param cb the end color
 * @param vert vertical gradient flag
 * @param src the image to draw on
 * 
 * @return void
 */
static void set_pixel(
    int x, int y,
    Circle *circ,
    Color ca, Color cb,
    int vert,
    Image *src)
{
    int dx = x - circ->center.val[0];
    int dy = y - circ->center.val[1];
    double alpha = (((double) dx) + circ->radius) / (2.0*circ->radius);
    if (vert) alpha = (((double) dy) + circ->radius) / (2.0*circ->radius);

    Color c;
    color_interpolate(&c, &ca, &cb, alpha);

    image_setColor(src, y, x, c);
}

/**
 * Reflects a dx and dy from a given center point around the eight axis of symmetry.
 * 
 * @param xc the center x coord
 * @param yc the center y coord
 * @param circ the circle being drawn
 * @param dx the delta in x
 * @param dy the delta in y
 * @param ca the start color value to set
 * @param cb the end color value to set
 * @param vert vertical gradient flag
 * @param src the image to update
 * 
 * @return void
 */
static void reflect_eight(
    int xc, int yc, int dx, int dy,
    Circle *circ,
    Color ca, Color cb,
    int vert, Image *src)
{
    set_pixel(xc + dx, yc + dy, circ, ca, cb, vert, src);
    set_pixel(xc - dx, yc + dy, circ, ca, cb, vert, src);
    set_pixel(xc + dx, yc - dy, circ, ca, cb, vert, src);
    set_pixel(xc - dx, yc - dy, circ, ca, cb, vert, src);

    set_pixel(xc + dy, yc + dx, circ, ca, cb, vert, src);
    set_pixel(xc - dy, yc + dx, circ, ca, cb, vert, src);
    set_pixel(xc + dy, yc - dx, circ, ca, cb, vert, src);
    set_pixel(xc - dy, yc - dx, circ, ca, cb, vert, src);
}

/**
 * Fill the row given the start and endpoint.
 * 
 * @param x0 the start x
 * @param y0 the start y
 * @param x1 the end x
 * @param y1 the end y
 * @param cl the circle to draw
 * @param ca the start color to draw
 * @param cb the end color to draw
 * @param vert vertical gradient flag
 * @param src the image to draw on
 * 
 * @return void
 */
static void fill_row(
    int x0, int y0, int x1, int y1,
    Circle *cl, Color ca, Color cb,
    int vert, Image *src)
{

    if (x0 > x1)
    {
        int xt = x0;
        x0 = x1;
        x1 = xt;
    }
    for (int x = x0; x < x1; x++)
    {
        set_pixel(x, y0, cl, ca, cb, vert, src);
    }
}

/**
 * Fill the rows in the circle.
 * 
 * @param xc the center x
 * @param yc the center y
 * @param dx the delta in x
 * @param dy the delta in y
 * @param cl the circle to draw
 * @param ca the start color to draw
 * @param cb the end color to draw
 * @param vert vertical gradient flag
 * @param src the image to draw on
 * 
 * @return void
 */
static void fill_rows(
    int xc, int yc, int dx, int dy,
    Circle *cl, Color ca, Color cb,
    int vert, Image *src)
{
    fill_row(xc - dx, yc + dy, xc + dx, yc + dy, cl, ca, cb, vert, src);
    fill_row(xc - dx, yc - dy, xc + dx, yc - dy, cl, ca, cb, vert, src);
    fill_row(xc - dy, yc - dx, xc + dy, yc - dx, cl, ca, cb, vert, src);
    fill_row(xc - dy, yc + dx, xc + dy, yc + dx, cl, ca, cb, vert, src);
}

/**
 * Implementatin of drawing the circle with optional fill param.
 * 
 * @param cl the circle to draw
 * @param src the image to draw on
 * @param ca the start color of the circle
 * @param cb the end color of the circle
 * @param fill flag to indicate if circle should be filled
 * @param vert vertical gradient flag
 * 
 * @return void
 */
static void draw_circle(Circle *cl, Image *src, Color ca, Color cb, int fill, int vert)
{
    double r = cl->radius;
    int xc = cl->center.val[0];
    int yc = cl->center.val[1];
    int dx = 0;
    int dy = r;
    int e = 1 - r;
    reflect_eight(xc, yc, dx, dy, cl, ca, cb, vert, src);

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
        reflect_eight(xc, yc, dx, dy, cl, ca, cb, vert, src);
        if (fill) fill_rows(xc, yc, dx, dy, cl, ca, cb, vert, src);
    }

    if (fill) fill_row(xc - r, yc, xc + r, yc, cl, ca, cb, vert, src);
}

void circle_set(Circle *circle, Point tp, double tr)
{
    circle->center = tp;
    circle->radius = tr;
}

// Implementatin inspired by circleMidpoint.c
void circle_draw(Circle *cl, Image *src, Color c)
{
    draw_circle(cl, src, c, c, 0, 0);
}

void circle_drawFill(Circle *cl, Image *src, Color c)
{
    draw_circle(cl, src, c, c, 1, 0);
}

void circle_drawG(Circle *cl, Image *src, Color ca, Color cb, int vert)
{
    draw_circle(cl, src, ca, cb, 0, vert);
}

void circle_drawFillG(Circle *cl, Image *src, Color ca, Color cb, int vert)
{
    draw_circle(cl, src, ca, cb, 1, vert);
}
