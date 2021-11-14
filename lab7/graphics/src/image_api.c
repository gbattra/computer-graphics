/**
 * Greg Attra
 * 09/25/2021
 * 
 * Executable to test the image API. Inspired by imagetest.c by Prof
 * Maxwell https://northeastern.instructure.com/courses/90450/assignments/1154396
 */

#include <math.h>
#include "image.h"
#include <stdio.h>


/**
 * Entrypoint for program to test image_api.c
 */
int main(int argc, char *argv[])
{
    Image *src;
    FPixel p = {rgb: {0.4, 0.6, 0.8}};
    int rows = 300;
    int cols = 400;
    int i, j;

    src = image_create(rows, cols);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            image_setc(src, i, j, 0, fabs(((float) (i-(rows/2))) / (rows/2)));
            image_setc(src, i, j, 1, fabs(((float) (j-(cols/2))) / (cols/2)));
            image_setc(src, i, j, 2, ((float) (i+j)) / (rows + cols));
        }
    }

    image_write(src, "output/lab2/colors.ppm");

    image_free(src);

    src = image_create(0, 0);
    rows = 400;
    cols = 600;

    image_alloc(src, rows, cols);
    image_write(src, "output/lab2/black.ppm");

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            image_setc(src, i, j, 0, p.rgb[0]);
            image_setc(src, i, j, 1, p.rgb[1]);
            image_setc(src, i, j, 2, p.rgb[2]);
        }
    }

    image_write(src, "output/lab2/skyblue.ppm");
    image_dealloc(src);
    image_free(src);
    return 0;
}
