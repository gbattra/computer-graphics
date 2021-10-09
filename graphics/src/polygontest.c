/**
 * Greg Attra
 * 10/08/2021
 * 
 * Executable to test polygon API implementation.
 */

#include "image.h"
#include "polygon.h"
#include "line.h"
#include "point.h"


int main(int argc, char *argv[])
{
    Image *src;
    src = image_create(600, 900);

    Color white = {1.0, 1.0, 1.0};
    Color red = {1.0, 0.0, 0.0};

    Point one;
    point_set2D(&one, src->cols / 3, src->rows / 3);

    Point two;
    point_set2D(&two, one.val[0] + src->cols / 3, one.val[1]);

    Point three;
    point_set2D(&three, two.val[0], two.val[1] + src->rows / 3);

    Point four;
    point_set2D(&four, one.val[0], three.val[1]);

    Point five;
    point_set2D(
        &five,
        one.val[0] / 2,
        (one.val[1] + three.val[1]) / 2);

    Point vlist[6] = {one, two, three, four, five, one};

    Polygon *pgon;
    pgon = polygon_createp(6, vlist);

    polygon_draw(pgon, src, white);

    polygon_drawFill(pgon, src, red);

    image_write(src, "output/lab4/polygon_outline.ppm");

    image_free(src);
    polygon_free(pgon);
}
