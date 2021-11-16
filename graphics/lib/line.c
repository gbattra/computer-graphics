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
    l->zBuffer = 1;
}

void line_set3D(Line *l, double x0, double y0, double z0, double x1, double y1, double z1)
{
    point_set3D(&l->a, x0, y0, z0);
    point_set3D(&l->b, x1, y1, z1);
    l->zBuffer = 1;
}

void line_set(Line *l, Point ta, Point tb)
{
    point_copy(&l->a, &ta);
    point_copy(&l->b, &tb);
    l->zBuffer = 1;
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

    float dx = fabs(l->b.val[0] - l->a.val[0]);
    float x = l->a.val[0];
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

    float dy = fabs(l->b.val[1] - l->a.val[1]);
    float y = l->a.val[1];
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

    float dy = l->b.val[1] - l->a.val[1];
    float dx = l->b.val[0] - l->a.val[0];
    float dz = ((1.0/l->b.val[2]) - (1.0/l->a.val[2]))/dx;
    float e = 2*dy - dx;

    float y = l->a.val[1];
    float x = l->a.val[0];
    float z = 1.0/l->a.val[2];
    printf("1: %f\n", z);
    for (int i = 0; i < abs(dx); i++)
    {
        double mag = ((double) i) / ((double) dx);
        color_interpolate(&c, &ca, &cb, mag);
        if ((l->zBuffer == 1 && z < image_getz(src, y, x)) || l->zBuffer == 0)
        {
            FPixel pix;
            pix.a = 1.0;
            pix.rgb[0] = c.c[0];
            pix.rgb[1] = c.c[1];
            pix.rgb[2] = c.c[2];
            pix.z = z;
            image_setf(src, y, x, pix);
        }
        z += dz;

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

    float dy = l->b.val[1] - l->a.val[1];
    float dx = l->b.val[0] - l->a.val[0];
    float dz = ((1.0/l->b.val[2]) - (1.0/l->a.val[2]))/dy;

    float y = l->a.val[1];
    float x = l->a.val[0];
    float z = 1.0/l->a.val[2];

    printf("2: %f\n", z);
    float e = 2*dx - dy;
    for (int i = 0; i < abs(dy); i++)
    {
        double mag = ((double) i) / ((double) dy);
        color_interpolate(&c, &ca, &cb, mag);
        if ((l->zBuffer == 1 && z < image_getz(src, y, x)) || l->zBuffer == 0)
        {
            FPixel pix;
            pix.a = 1.0;
            pix.rgb[0] = c.c[0];
            pix.rgb[1] = c.c[1];
            pix.rgb[2] = c.c[2];
            pix.z = z;
            image_setf(src, y, x, pix);
        }
        z += dz;

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

    float dy = l->b.val[1] - l->a.val[1];
    float dx = l->b.val[0] - l->a.val[0];
    float dz = ((1.0/l->b.val[2]) - (1.0/l->a.val[2]))/dy;

    float y = l->b.val[1];
    float x = l->b.val[0];
    float z = 1.0/l->b.val[2];
    printf("3: %f\n", z);

    float e = 2*dx + dy;

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
        if ((l->zBuffer == 1 && z < image_getz(src, y, x)) || l->zBuffer == 0)
        {
            FPixel pix;
            pix.a = 1.0;
            pix.rgb[0] = c.c[0];
            pix.rgb[1] = c.c[1];
            pix.rgb[2] = c.c[2];
            pix.z = z;
            image_setf(src, y, x, pix);
        }
        z += dz;
    }
    
}

static void line_draw4(Image *src, Line *l, Color ca, Color cb)
{
    Color c;
    color_copy(&c, &ca);

    float dy = l->b.val[1] - l->a.val[1];
    float dx = l->b.val[0] - l->a.val[0];
    float dz = ((1.0/l->b.val[2]) - (1.0/l->a.val[2]))/dx;

    float y = l->b.val[1];
    float x = l->b.val[0];
    float z = 1.0/l->b.val[2];

    printf("4: %f\n", z);

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
        if ((l->zBuffer == 1 && z < image_getz(src, y, x)) || l->zBuffer == 0)
        {
            FPixel pix;
            pix.a = 1.0;
            pix.rgb[0] = c.c[0];
            pix.rgb[1] = c.c[1];
            pix.rgb[2] = c.c[2];
            pix.z = z;
            image_setf(src, y, x, pix);
        }
        z += dz;
    }
}

void line_draw(Line *l, Image *src, Color c)
{
    line_drawG(l, src, c, c);
}

void line_drawG(Line *l, Image *src, Color ca, Color cb)
{
    float x0 = l->a.val[0];
    float y0 = l->a.val[1];
    float z0 = l->a.val[2];

    float x1 = l->b.val[0];
    float y1 = l->b.val[1];
    float z1 = l->b.val[2];

    if (x0 > x1)
    {
        float xt = x0;
        x0 = x1;
        x1 = xt;

        float yt = y0;
        y0 = y1;
        y1 = yt;

        float zt = z0;
        z0 = z1;
        z1 = zt;
    }

    Line tmp;
    line_set3D(&tmp, x0, y0, z0, x1, y1, z1);

    if (y0 == y1) return line_drawHorizontal(src, &tmp, ca, cb);
    if (x0 == x1) return line_drawVertical(src, &tmp, ca, cb);

    float dx = x1 - x0;
    float dy = y1 - y0;
    float m = dy / dx;

    if (0 < m && m <= 1) return line_draw1(src, &tmp, ca, cb);
    if (m > 1) return line_draw2(src, &tmp, ca, cb);
    if (m < -1) return line_draw3(src, &tmp, ca, cb);
    if (0 > m && m >= -1) return line_draw4(src, &tmp, ca, cb);
}
