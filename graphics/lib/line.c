/**
 * Greg Attra
 * 09/30/2021
 * 
 * Implementation of the Line API defined in line.h
 */

#include "line.h"
#include "image.h"
#include "point.h"
#include <stdlib.h>
#include <math.h>


void line_print(Line *l, FILE *fp)
{
    fprintf(fp, "Line: ");
    point_print(&l->a, fp);
    fprintf(fp, " | ");
    point_print(&l->b, fp);
    fprintf(fp, "\n");
}

void line_set2D(Line *l, double x0, double y0, double x1, double y1)
{
    point_set2D(&l->a, x0, y0);
    point_set2D(&l->b, x1, y1);
}

void line_set3D(Line *l, double x0, double y0, double z0, double x1, double y1, double z1)
{
    point_set3D(&l->a, x0, y0, z0);
    point_set3D(&l->b, x1, y1, z1);
}

void line_set(Line *l, Point ta, Point tb)
{
    point_copy(&l->a, &ta);
    point_copy(&l->b, &tb);
}

void line_zBuffer(Line *l, int flag)
{
    l->zBuffer = flag;
}

void line_normalize(Line *l)
{
    point_normalize(&l->a);
    point_normalize(&l->b);
}

void line_copy(Line *to, Line *from)
{
    to->zBuffer = from->zBuffer;
    point_copy(&to->a, &from->a);
    point_copy(&to->b, &from->b);
}

static void line_drawHorizontal(Image *src, Line *l, Color ca, Color cb)
{
    Color c;
    color_copy(&c, &ca);

    int dx = fabs(l->b.val[0] - l->a.val[0]);
    int x = l->a.val[0];
    if (l->a.val[0] > l->b.val[0]) x = l->b.val[0];
    
    for (int i = 0; i < dx; i++)
    {
        double mag = ((double) i) / ((double) dx);
        color_interpolate(&c, &ca, &cb, mag);
        image_setColor(src, l->a.val[1], x, c);
        x++;
    }
}

static void line_drawVertical(Image *src, Line *l, Color ca, Color cb)
{
    Color c;
    color_copy(&c, &ca);

    int dy = fabs(l->b.val[1] - l->a.val[1]);
    int y = l->a.val[1];
    if (l->a.val[1] > l->b.val[1]) y = l->b.val[1];

    for (int i = 0; i < dy; i++)
    {
        double mag = ((double) i) / ((double) dy);
        color_interpolate(&c, &ca, &cb, mag);
        image_setColor(src, y, l->a.val[0], c);
        y++;
    }
}

static void line_draw1(Image *src, Line *l, Color ca, Color cb)
{
    Color c;
    color_copy(&c, &ca);

    int dy = l->b.val[1] - l->a.val[1];
    int dx = l->b.val[0] - l->a.val[0];
    int e = 2*dy - dx;

    int y = l->a.val[1];
    int x = l->a.val[0];
    for (int i = 0; i < abs(dx); i++)
    {
        double mag = ((double) i) / ((double) dx);
        color_interpolate(&c, &ca, &cb, mag);
        image_setColor(src, y, x, c);

        if (e > 0)
        {
            e -= 2*dx;
            y++;
        }
        e += 2*dy;
        x++;
    }
}

static void line_draw2(Image *src, Line *l, Color ca, Color cb)
{
    Color c;
    color_copy(&c, &ca);

    int dy = l->b.val[1] - l->a.val[1];
    int dx = l->b.val[0] - l->a.val[0];

    int y = l->a.val[1];
    int x = l->a.val[0];

    int e = 2*dx - dy;
    for (int i = 0; i < abs(dy); i++)
    {
        double mag = ((double) i) / ((double) dy);
        color_interpolate(&c, &ca, &cb, mag);
        image_setColor(src, y, x, c);

        if (e > 0)
        {
            e -= 2*dy;
            x++;
        }
        e += 2*dx;
        y++;
    }
}

static void line_draw3(Image *src, Line *l, Color ca, Color cb)
{
    Color c;
    color_copy(&c, &ca);

    int dy = l->b.val[1] - l->a.val[1];
    int dx = l->b.val[0] - l->a.val[0];

    int y = l->b.val[1];
    int x = l->b.val[0];

    int e = 2*dx + dy;

    for (int i = 0; i < abs(dy); i++)
    {
        if (e > 0)
        {
            e += 2*dy;
            x--;
        }
        e += 2*dx;
        y++;
        
        double mag = ((double) i) / ((double) dy);
        color_interpolate(&c, &ca, &cb, mag);
        image_setColor(src, y, x, c);
    }
    
}

static void line_draw4(Image *src, Line *l, Color ca, Color cb)
{
    Color c;
    color_copy(&c, &ca);

    int dy = l->b.val[1] - l->a.val[1];
    int dx = l->b.val[0] - l->a.val[0];

    int y = l->b.val[1];
    int x = l->b.val[0];

    int e = 2*dy + dx;
    for (int i = 0; i < abs(dx); i++)
    {
        if (e > 0)
        {
            e -= 2*dx;
            y++;
        }
        e -= 2*dy;
        x--;

        double mag = ((double) i) / ((double) dx);
        color_interpolate(&c, &ca, &cb, mag);
        image_setColor(src, y, x, c);
    }
}

void line_draw(Line *l, Image *src, Color c)
{
    line_drawG(l, src, c, c);
}

void line_drawG(Line *l, Image *src, Color ca, Color cb)
{
    int y0 = l->a.val[1];
    int y1 = l->b.val[1];
    int x0 = l->a.val[0];
    int x1 = l->b.val[0];

    if (x0 > x1)
    {
        int xt = x0;
        x0 = x1;
        x1 = xt;

        int yt = y0;
        y0 = y1;
        y1 = yt;
    }

    Line tmp;
    tmp.zBuffer = l->zBuffer;
    line_set3D(&tmp, x0, y0, l->a.val[2], x1, y1, l->b.val[2]);

    if (y0 == y1) return line_drawHorizontal(src, &tmp, ca, cb);
    if (x0 == x1) return line_drawVertical(src, &tmp, ca, cb);

    int dx = x1 - x0;
    int dy = y1 - y0;
    float m = (float) dy / (float) dx;

    if (0 < m && m <= 1) return line_draw1(src, &tmp, ca, cb);
    if (m > 1) return line_draw2(src, &tmp, ca, cb);
    if (m < -1) return line_draw3(src, &tmp, ca, cb);
    if (0 > m && m >= -1) return line_draw4(src, &tmp, ca, cb);
}
