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
 * Draw horizontal lines between the reflection points.
 * 
 * @param cx the center x coord
 * @param cy the center y coord
 * @param dx the delta in x
 * @param dy the delta in y
 * @param src the image to draw on
 * @param c the color of the lines
 * 
 * @return void
 */
static void fill_reflections(int cx, int cy, int dx, int dy, Image *src, Color c)
{
    fill_row(cx - dx, cy + dy, cx + dx, cy + dy, c, src);
    fill_row(cx - dx, cy - dy, cx + dx, cy - dy, c, src);
}

/**
 * Plot the reflection points on the elipse.
 * 
 * @param cx the center x coord
 * @param cy the center y coord
 * @param dx the delta in x
 * @param dy the delta in y
 * @param src the image to draw on
 * @param c the color of the points
 * 
 * @return void
 */
static void plot_reflections(int cx, int cy, int dx, int dy, Image *src, Color c)
{
    FPixel pix;
    pix.rgb[0] = c.c[0];
    pix.rgb[1] = c.c[1];
    pix.rgb[2] = c.c[2];

    set_pixel(cx + dx, cy + dy, src, pix);
    set_pixel(cx - dx, cy + dy, src, pix);
    set_pixel(cx + dx, cy - dy, src, pix);
    set_pixel(cx - dx, cy - dy, src, pix);
}


void elipse_set(Elipse *el, Point center, double ra, double rb, double a)
{
    el->a = a;
    el->ra = ra;
    el->rb = rb;
    point_copy(&el->c, &center);
}

// inspired by Prof. Maxwell's notes: CS5310-F21-Lectures.pdf
static void draw_elipse(Elipse *el, Image *src, Color c, int fill)
{
    int cx = el->c.val[0];
    int cy = el->c.val[1];
    int ry = el->rb;
    int rx = el->ra;
    int dx = -1;
    int dy = -ry;
    int px = 2 * ry * ry;
    int py = 2 * rx * rx * -dy;

    image_setColor(src, cy + ry, cx, c);
    image_setColor(src, cy - ry, cx, c);

    int p = (ry * ry) - (rx * rx * ry) + (rx * rx) / 4 + (ry*ry) + px;

    plot_reflections(cx, cy, dx, dy, src, c);
    if (fill) fill_reflections(cx, cy, dx, dy, src, c);

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
        plot_reflections(cx, cy, dx, dy, src, c);
        if (fill) fill_reflections(cx, cy, dx, dy, src, c);
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
        plot_reflections(cx, cy, dx, dy, src, c);
        if (fill) fill_reflections(cx, cy, dx, dy, src, c);
    }
}

void elipse_draw(Elipse *el, Image *src, Color c)
{
    draw_elipse(el, src, c, 0);
}

void elipse_drawFill(Elipse *el, Image *src, Color c)
{
    draw_elipse(el, src, c, 1);
}
