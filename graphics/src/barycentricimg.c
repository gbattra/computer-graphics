/**
 * Greg Attra
 * 10/11/2021
 * 
 * Executable for generating an image using barycentric fill
 * and blending the colors.
 */

#include "graphics.h"
#include <math.h>

int main(int argc, char *argv[])
{
    Color white = {1.0, 1.0, 1.0};

    int length = 900 / 5.5;
    int height = sqrt(((length/2)*(length/2) + (length * length)));

    Image *src;
    src = image_create((height * 10) + 1, 900);
    for (int i = height; i < src->rows; i+=height)
    {
        int y0 = i - height;
        int y1 = i;

        for (int j = length; j < src->cols; j+=length)
        {
            int x0 = j - length;
            int x1 = j;

            Point vlist[3];
            point_set2D(&vlist[0], x0, y0);
            point_set2D(&vlist[1], x1, y0);
            point_set2D(&vlist[2], x0 + (length / 2), y1);
            Polygon *t1;
            t1 = polygon_createp(3, vlist);
            
            point_set2D(&vlist[0], x0 + (length / 2), y1);
            point_set2D(&vlist[1], x1, y0);
            point_set2D(&vlist[2], x1 + (length / 2), y1);
            Polygon *t2;
            t2 = polygon_createp(3, vlist);

            polygon_draw(t1, src, white);
            polygon_draw(t2, src, white);

            polygon_free(t1);
            polygon_free(t2);
        }
    }

    image_write(src, "output/lab4/barycentric.ppm");
    image_free(src);

    return 0;
}
