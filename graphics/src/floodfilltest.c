/**
 * Greg Attra
 * 10/04/2021
 * 
 * Executable to test the flood fill functionality.
 */

#include "floodfill.h"
#include "image.h"
#include "polyline.h"


int main(int argc, char *argv[])
{
    Color white = {1.0, 1.0, 1.0};
    Image *src;
    src = image_create(400, 600);
    
    Point one;
    point_set2D(&one, src->cols / 3, src->rows / 3);

    Point two;
    point_set2D(&two, one.val[0], one.val[1] + src->rows / 3);

    Point three;
    point_set2D(&three, one.val[0] + src->cols / 3, two.val[1]);

    Point four;
    point_set2D(&four, one.val[0] + src->cols / 3, one.val[1]);

    Point five;
    point_copy(&five, &one);

    Point vlist[5] = {one, two, three, four, five};
    Polyline *pline = polyline_createp(5, vlist);

    polyline_draw(pline, src, white);
    polyline_free(pline);

    image_write(src, "output/lab3/floodfill.ppm");
    image_free(src);
}
