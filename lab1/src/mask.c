/**
 * Greg Attra
 * 09/20/2021
 * 
 * Program to generate a foreground mask on a blue/green screen image.
 */

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

/**
 * String describing program usage.
 */
char *usage_str =
    "Usage:\n"
    "> mask <source ppm file> <output ppm file> <thresh>\n";

/**
 * Reads in source image. Iterates over each pixel and determines if red channel
 * is > the avg of the blue/green channels + a THRESH. If true, pixel is set to 255,
 * otherwise 0.
 * 
 * @param argc arg count
 * @param argv arg pointers
 * 
 * @return 0 success -1 fail
 */
int main(int argc, char *argv[])
{
    Pixel *img;
    int rows, cols, colors;
    long imagesize;
    long i, avg_delta;

    if (argc < 4)
    {
        printf(usage_str);
        exit(-1);
    }

    img = readPPM(&rows, &cols, &colors, argv[1]);
    if (!img)
    {
        fprintf(stderr, "Unable to read %s\n", argv[1]);
        exit(-1);
    }

    imagesize = (long) rows * (long) cols;

    for (i = 0; i < imagesize; i++)
    {
        avg_delta = (int) img[i].r - ((int) img[i].g + (int) img[i].b) / 2;
        if (avg_delta < atoi(argv[3]))
        {
            img[i].g = 0;
            img[i].r = 0;
            img[i].b = 0;
        }
        else
        {
            img[i].g = 255;
            img[i].r = 255;
            img[i].b = 255;
        }
    }
    
    writePPM(img, rows, cols, colors, argv[2]);

    free(img);

    return 0;
}
