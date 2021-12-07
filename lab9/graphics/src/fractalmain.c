/**
 * Greg Attra
 * 09/29/2021
 * 
 * Executable for running fractal programs.
 */

#include "image.h"
#include "fractals.h"
#include "noise.h"
#include "ppmIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *usage_str =
    "Usage:\n"
    "fractalmain flag x0 y0 dx rows cols filename\n";

static void foggy()
{
    Image *bg;
    bg = image_read("source/haunted.ppm");
    Image *noise;
    noise = image_create(bg->rows, bg->cols);
    perlin(noise, 9);
    for (int i = 0; i < bg->rows; i++)
    {
        for (int j = 0; j < bg->cols; j++)
        {
            FPixel *bg_pix = &bg->data[(i * bg->cols) + j];
            FPixel *noise_pix = &noise->data[(i * noise->cols) + j];

            float alpha = noise_pix->rgb[0];
            float dark = 0.0;

            bg_pix->rgb[0] = (1.0-alpha) * (bg_pix->rgb[0] - dark) + (alpha * 1.0 + dark);
            bg_pix->rgb[1] = (1.0-alpha) * (bg_pix->rgb[1] - dark) + (alpha * 1.0 + dark);
            bg_pix->rgb[2] = (1.0-alpha) * (bg_pix->rgb[2] - dark) + (alpha * 1.0 + dark);

            if (bg_pix->rgb[0] > 1.0) bg_pix->rgb[0] = 1.0;
            if (bg_pix->rgb[1] > 1.0) bg_pix->rgb[1] = 1.0;
            if (bg_pix->rgb[2] > 1.0) bg_pix->rgb[2] = 1.0;

            if (bg_pix->rgb[0] < 0.0) bg_pix->rgb[0] = 0.0;
            if (bg_pix->rgb[1] < 0.0) bg_pix->rgb[1] = 0.0;
            if (bg_pix->rgb[2] < 0.0) bg_pix->rgb[2] = 0.0;
        }
    }
    image_write(bg, "output/lab2/foggy.ppm");
}


int main(int argc, char *argv[])
{
    char *flag = argv[1];
    char c_flag = 'c';
    if (strcmp(&c_flag, flag) == 0)
    {
        foggy();
        return 0;
    }

    if (argc < 8)
    {
        printf("%s\n", usage_str);
    }

    float x0 = atof(argv[2]);
    float y0 = atof(argv[3]);
    float dx = atof(argv[4]);
    int rows = atoi(argv[5]);
    int cols = atoi(argv[6]);

    Image *src;
    src = image_create(rows, cols);

    char j_flag = 'j';
    char m_flag = 'm';
    if (strcmp(&j_flag, flag) == 0)
    {
        julia(src, x0, y0, dx);
    }
    else if (strcmp(&m_flag, flag) == 0)
    {
        mandelbrot(src, x0, y0, dx);
    }

    image_write(src, argv[7]);
}
