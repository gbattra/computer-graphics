/**
 * Greg Attra
 * 10/11/2021
 * 
 * Executable for generating an image using barycentric fill
 * and blending the colors.
 */

#include "graphics.h"
#include <math.h>

/**
 * Draw the traingle given the points.
 * 
 * @param xa the x coord for point A
 * @param ya the y coord for point A
 * @param xb the x coord for point B
 * @param yb the y coord for point B
 * @param xc the x coord for point C
 * @param yc the y coord for point C
 * @param src the image to draw on
 * 
 * @return void
 */
static void draw_triangles(int xa, int ya, int xb, int yb, int xc, int yc, Image *src)
{
    Color ac =
    {
        (float) rand() / (float) RAND_MAX,
        (float) rand() / (float) RAND_MAX,
        (float) rand() / (float) RAND_MAX
    };
    Color bc =
    {
        (float) rand() / (float) RAND_MAX,
        (float) rand() / (float) RAND_MAX,
        (float) rand() / (float) RAND_MAX
    };
    Color cc =
    {
        (float) rand() / (float) RAND_MAX,
        (float) rand() / (float) RAND_MAX,
        (float) rand() / (float) RAND_MAX
    };

    Point vlist[3];
    point_set2D(&vlist[0], xa, ya);
    point_set2D(&vlist[1], xb, yb);
    point_set2D(&vlist[2], xc, yc);
    Polygon *t;
    t = polygon_createp(3, vlist);
    polygon_blendFillB(t, src, ac, bc, cc);
    polygon_free(t);
}

int main(int argc, char *argv[])
{
    int length = 900 / 5.5;
    int height = sqrt(((length/2)*(length/2) + (length * length)));

    Image *src;
    src = image_create((height * 5) + 1, 900);
    for (int i = height; i < src->rows; i+=height)
    {
        int y0 = i - height;
        int y1 = i;

        for (int j = length; j < src->cols; j+=length)
        {
            int x0 = j - length;
            int x1 = j;

            draw_triangles(x0, y0, x1, y0, x0 + (length / 2), y1, src);
            draw_triangles(x0 + (length / 2), y1, x1, y0, x1 + (length / 2), y1, src);
        }
    }

    for (int i = height; i < src->rows; i+=height)
    {
        int y0 = i - height;
        int y1 = i;

        draw_triangles(0, y0, 0, y1, (length / 2), y1, src);
        draw_triangles(src->cols - (length / 2), y0, src->cols, y0, src->cols, y1, src);
    }



    image_write(src, "output/lab4/barycentric.ppm");
    image_free(src);

    return 0;
}
