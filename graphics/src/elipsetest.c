/**
 * Greg Attra
 * 09/30/2021
 * 
 * Test program for Elipse API.
 */

#include "image.h"
#include "elipse.h"
#include "point.h"


int main(int argc, char *argv[])
{
    Image *src;
    src = image_create(400, 800);

    Elipse el;
    el.ra = 100.0;
    el.rb = 50.0;
    point_set2D(&el.c, 400, 200);

    Color color;
    color_set(&color, 1.0, 1.0, 1.0);

    elipse_draw(&el, src, color);

    image_write(src, "output/lab3/elipse_outline.ppm");

    image_reset(src);
    elipse_drawFill(&el, src, color);

    image_write(src, "output/lab3/elipse_fill.ppm");

    image_free(src);
}
