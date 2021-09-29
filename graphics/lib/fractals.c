/**
 * Greg Attra
 * 09/27/2021
 * 
 * Implementation of the Julia function.
 */

#include "fractals.h"
#include <stdio.h>
#include <math.h>

#define IN_SET 1.0
#define OUT_SET 0.0
#define MAX_ITER 1000
#define C1 0.7454054
#define C2 0.1130063


void mandelbrot(Image *dst, float x0, float y0, float dx)
{
    float dy = (float) dst->rows / (float) (dst->cols / dx);
    float x1 = x0 + dx;
    float y1 = y0 + dy;
    float scale_cols = dx / (float) dst->cols;
    float scale_rows = dy / (float) dst->rows;
    for (int i = 0; i < dst->rows; i++)
    {
        for (int j = 0; j < dst->cols; j++)
        {
            int iter = 0;
            float zx = 0;
            float zy = 0;
            float z = 0;
            float cx = scale_cols * j + x0;
            float cy = -scale_rows * i + y1;
            while (sqrtf(z) < 2 && iter < MAX_ITER)
            {
                float zx_n = (zx * zx) - (zy * zy) + cx;
                float zy_n = 2 * zx * zy - cy;
                zx = zx_n;
                zy = zy_n;
                z = (zx*zx) + (zy*zy);
                iter++;
            }

            float scale_color = iter % MAX_ITER;
            float color[3] = {0.4 * scale_color, 0.6 * scale_color, 0.8 * scale_color};

            FPixel *pix = &dst->data[(i * dst->cols) + j];
            pix->rgb[0] = color[0];
            pix->rgb[1] = color[1];
            pix->rgb[2] = color[2];
        }
    }
}


void julia(Image *dst, float x0, float y0, float dx)
{
    float dy = (float) dst->rows / (float) (dst->cols / dx);
    float x1 = x0 + dx;
    float y1 = y0 + dy;
    float scale_cols = dx / (float) dst->cols;
    float scale_rows = dy / (float) dst->rows;
    for (int i = 0; i < dst->rows; i++)
    {
        for (int j = 0; j < dst->cols; j++)
        {
            int iter = 0;
            float z = sqrtf((x0*x0) + (y0*y0) + 0.00001);
            while (z < 2 && iter < MAX_ITER)
            {
                printf("%i\n", iter);
                z = (z*z) - (C1 + i * C2);
                iter++;
            }

            float scale_color = iter % MAX_ITER;
            float color[3] = {0.4 * scale_color, 0.6 * scale_color, 0.8 * scale_color};

            FPixel *pix = &dst->data[(i * dst->cols) + j];
            pix->rgb[0] = color[0];
            pix->rgb[1] = color[1];
            pix->rgb[2] = color[2];
        }
    }
}
