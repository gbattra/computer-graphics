/**
 * Greg Attra
 * 10/01/2021
 * 
 * Implementation of the Elipse API defined in elipse.h
 */

#include "elipse.h"
#include "point.h"
#include "image.h"
#include "line.h"

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
    Elipse *el,
    Color ca, Color cb,
    int vert,
    Image *src)
{
    // int dx = x - el->c.val[0];
    // int dy = y - el->c.val[1];
    // double alpha = (((double) dx) + el->ra) / (2.0*el->ra);
    // if (vert) alpha = (((double) dy) + el->rb) / (2.0*el->rb);

    // Color c;
    // color_interpolate(&c, &ca, &cb, alpha);

    image_setColor(src, y, x, ca);
}

/**
 * Fill the row given the start and endpoint.
 * 
 * @param x0 the start x
 * @param y0 the start y
 * @param x1 the end x
 * @param y1 the end y
 * @param el the elipse being drawn
 * @param ca the start color
 * @param cb the end color
 * @param vert vertical gradient flag
 * @param src the image to draw on
 * 
 * @return void
 */
static void fill_row(
    int x0, int y0, int x1, int y1,
    Elipse *el, Color ca, Color cb,
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
        set_pixel(x, y0, el, ca, cb, vert, src);
    }
}

/**
 * Draw horizontal lines between the reflection points.
 * 
 * @param cx the center x coord
 * @param cy the center y coord
 * @param dx the delta in x
 * @param dy the delta in y
 * @param el the elipse being drawn
 * @param ca the start color
 * @param cb the end color
 * @param vert vertical gradient flag
 * @param src the image to draw on
 * 
 * @return void
 */
static void fill_reflections(
    int cx, int cy, int dx, int dy,
    Elipse *el, Color ca, Color cb,
    int vert, Image *src)
{
    fill_row(cx - dx, cy + dy, cx + dx, cy + dy, el, ca, cb, vert, src);
    fill_row(cx - dx, cy - dy, cx + dx, cy - dy, el, ca, cb, vert, src);
}

/**
 * Plot the reflection points on the elipse.
 * 
 * @param cx the center x coord
 * @param cy the center y coord
 * @param dx the delta in x
 * @param dy the delta in y
 * @param el the elipse being drawn
 * @param ca the start color
 * @param cb the end color
 * @param vert vertical gradient flag
 * @param src the image to draw on
 * 
 * @return void
 */
static void plot_reflections(
    int cx, int cy, int dx, int dy,
    Elipse *el, Color ca, Color cb,
    int vert, Image *src)
{
    set_pixel(cx + dx, cy + dy, el, ca, cb, vert, src);
    set_pixel(cx - dx, cy + dy, el, ca, cb, vert, src);
    set_pixel(cx + dx, cy - dy, el, ca, cb, vert, src);
    set_pixel(cx - dx, cy - dy, el, ca, cb, vert, src);
}

void elipse_set(Elipse *el, Point center, double ra, double rb, double a)
{
    el->a = a;
    el->ra = ra;
    el->rb = rb;
    point_copy(&el->c, &center);
}

// inspired by Prof. Maxwell's notes: CS5310-F21-Lectures.pdf
static void draw_elipse(Elipse *el, Image *src, Color ca, Color cb, int vert, int fill)
{
    int cx = el->c.val[0];
    int cy = el->c.val[1];
    int ry = el->rb;
    int rx = el->ra;
    int dx = -1;
    int dy = -ry;
    int px = 2 * ry * ry;
    int py = 2 * rx * rx * -dy;

    image_setColor(src, cy + ry, cx, cb);
    image_setColor(src, cy - ry, cx, ca);

    int p = (ry * ry) - (rx * rx * ry) + (rx * rx) / 4 + (ry*ry) + px;

    plot_reflections(cx, cy, dx, dy, el, ca, cb, vert, src);
    if (fill) fill_reflections(cx, cy, dx, dy, el, ca, cb, vert, src);

    while (px < py)
    {
        dx--;
        px += 2 * ry * ry;
        if (p < 0)
        {
            p += ry * ry + px;
        }
        else
        {
            dy++;
            py -= 2 * rx * rx;
            p += ry * ry + px - py;
        }
        plot_reflections(cx, cy, dx, dy, el, ca, cb, vert, src);
        if (fill) fill_reflections(cx, cy, dx, dy, el, ca, cb, vert, src);
    }

    p = ry * ry * (dx * dx + dx) + rx * rx * (dy * dy - 2 * dy + 1) - rx * rx * ry * ry + rx * rx - py;
    
    while (dy < 0)
    {
        dy++;
        py -= 2 * rx * rx;
        if (p > 0)
        {
            p += rx * rx - py;
        }
        else
        {
            dx--;
            px += 2 * ry * ry;
            p += rx * rx - py + px;
        }
        plot_reflections(cx, cy, dx, dy, el, ca, cb, vert, src);
        if (fill) fill_reflections(cx, cy, dx, dy, el, ca, cb, vert, src);
    }
}

void elipse_draw(Elipse *el, Image *src, Color c)
{
    draw_elipse(el, src, c, c, 0, 0);
}

void elipse_drawFill(Elipse *el, Image *src, Color c)
{
    draw_elipse(el, src, c, c, 0, 1);
}

void elipse_drawG(Elipse *el, Image *src, Color ca, Color cb, int vert)
{}

void elipse_drawFillG(Elipse *el, Image *src, Color ca, Color cb, int vert)
{}
