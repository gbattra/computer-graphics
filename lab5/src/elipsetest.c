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

    Color white = {1.0, 1.0, 1.0};
    Color gray = {0.25, 0.25, 0.25};

    Image *src;
    src = image_create(500, 900);

    Elipse el;
    el.ra = 100.0;
    el.rb = 50.0;

    point_set2D(&el.c, 200, 100);
    elipse_draw(&el, src, white);

    point_set2D(&el.c, 200, 250);
    elipse_drawFill(&el, src, white);
    
    point_set2D(&el.c, 450, 100);
    elipse_drawG(&el, src, white, gray, 0);

    point_set2D(&el.c, 450, 250);
    elipse_drawG(&el, src, white, gray, 1);

    point_set2D(&el.c, 700, 100);
    elipse_drawFillG(&el, src, white, gray, 0);

    point_set2D(&el.c, 700, 250);
    elipse_drawFillG(&el, src, white, gray, 1);

    image_write(src, "output/lab3/elipse.ppm");

    image_free(src);
}
