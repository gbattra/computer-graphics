/**
 * Greg Attra
 * 09/30/2021
 * 
 * Test program for Circle API.
 */

#include "image.h"
#include "circle.h"
#include "point.h"


int main(int argc, char *argv[])
{
    Image *src;
    src = image_create(400, 800);

    Circle c;
    c.radius = 50.0;
    point_set2D(&c.center, 400, 200);

    Color color;
    color_set(&color, 1.0, 1.0, 1.0);

    circle_draw(&c, src, color);

    image_write(src, "output/lab3/circle.ppm");
}
