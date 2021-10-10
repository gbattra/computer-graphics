/**
 * Greg Attra
 * 10/10/2021
 * 
 * Image of a rocket for Lab 4 part 4.
 */

#include "graphics.h"
#include <math.h>

int main(int argc, char *argv[])
{
    Color white = {1.0, 1.0, 1.0};
    Color gray = {0.5, 0.5, 0.5};
    Image *src;
    src = image_create(900, 500);

    Point shipbody[11];
    point_set2D(&shipbody[0], src->cols / 2, 50);
    point_set2D(&shipbody[1], (src->cols / 2) + 25, 100);
    point_set2D(&shipbody[2], (src->cols / 2) + 25, 300);
    point_set2D(&shipbody[3], (src->cols / 2) + 50, 350);
    point_set2D(&shipbody[8], (src->cols / 2) - 50, 350);
    point_set2D(&shipbody[9], (src->cols / 2) - 25, 300);
    point_set2D(&shipbody[10], (src->cols / 2) - 25, 100);
    point_set2D(&shipbody[4], (src->cols / 2) + 65, 400);
    point_set2D(&shipbody[5], (src->cols / 2) + 50, 425);
    point_set2D(&shipbody[6], (src->cols / 2) - 50, 425);
    point_set2D(&shipbody[7], (src->cols / 2) - 65, 400);
    point_set2D(&shipbody[8], (src->cols / 2) - 50, 350);
    point_set2D(&shipbody[9], (src->cols / 2) - 25, 300);
    point_set2D(&shipbody[10], (src->cols / 2) - 25, 100);

    Polygon *shipbody_pgon;
    shipbody_pgon = polygon_createp(11, shipbody);
    polygon_draw(shipbody_pgon, src, white);
    polygon_free(shipbody_pgon);

    Circle circles[15];
    Point p[15];
    point_set2D(&p[0], (src->cols / 2), 425);
    circle_set(&circles[0], p[0], 10.0);
    point_set2D(&p[1], (src->cols / 2), 445);
    circle_set(&circles[1], p[1], 15.0);
    point_set2D(&p[2], (src->cols / 2), 485);
    circle_set(&circles[2], p[2], 30.0);
    point_set2D(&p[3], (src->cols / 2), 555);
    circle_set(&circles[3], p[3], 60.0);
    point_set2D(&p[4], (src->cols / 2), 630);
    circle_set(&circles[4], p[4], 90.0);
    point_set2D(&p[5], (src->cols / 2), 750);
    circle_set(&circles[5], p[5], 160.0);
    point_set2D(&p[6], (src->cols / 2), 1000);
    circle_set(&circles[6], p[6], 300.0);

    for (int i = 0; i < 15; i++)
    {
        circle_drawFill(&circles[i], src, gray);
    }

    image_write(src, "output/lab4/rocket.ppm");

    image_free(src);

    return 0;
}
