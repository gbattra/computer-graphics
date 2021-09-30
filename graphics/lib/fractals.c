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
#define MAX_ITER 100
#define C1 0.7454054
#define C2 0.1130063


void mandelbrot(Image *dst, float x0, float y0, float dx)
{
    float dy = (float) dst->rows / (float) (((float) dst->cols) / dx);
    float y1 = y0 + dy;
    float scale_cols = dx / (float) dst->cols;
    float scale_rows = dy / (float) dst->rows;

    for (int i = 0; i < dst->rows; i++)
    {
        for (int j = 0; j < dst->cols; j++)
        {
            float zx = 0;
            float zy = 0;
            float cx = scale_cols * j + x0;
            float cy = -scale_rows * i + y1;
            int iter = 0;
            while ((zx * zx) + (zy*zy) < 4 && iter < MAX_ITER)
            {
                float tmp = (zx * zx) - (zy * zy) + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tmp;
                iter++;
            }

            float scale_color = 1.0;
            if (iter == MAX_ITER) scale_color = 0.0;
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
    float cx = -0.7;
    float cy = 0.27015;
    float dy = (float) dst->rows / (float) (((float) dst->cols) / dx);
    float y1 = y0 + dy;
    float scale_cols = dx / (float) dst->cols;
    float scale_rows = dy / (float) dst->rows;

    for (int i = 0; i < dst->rows; i++)
    {
        for (int j = 0; j < dst->cols; j++)
        {
            float zx = scale_cols * j + x0;
            float zy = -scale_rows * i + y1;
            int iter = 0;
            while ((zx * zx) + (zy*zy) < 4 && iter < MAX_ITER)
            {
                float tmp = (zx * zx) - (zy * zy) + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tmp;
                iter++;
            }

            float scale_color = 1.0;
            if (iter == MAX_ITER) scale_color = 0.0;
            float color[3] = {0.4 * scale_color, 0.6 * scale_color, 0.8 * scale_color};

            FPixel *pix = &dst->data[(i * dst->cols) + j];
            pix->rgb[0] = color[0];
            pix->rgb[1] = color[1];
            pix->rgb[2] = color[2];
        }
    }
}
