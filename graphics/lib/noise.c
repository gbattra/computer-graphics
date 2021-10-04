/**
 * Greg Attra
 * 09/29/2021
 * 
 * Implementation of functions defined in perlin.h
 */

#include "stdio.h"
#include "stdlib.h"
#include "noise.h"
#include "math.h"

// credit https://youtu.be/6-0UaeJBumA
void perlin(Image *dst, int n_octaves)
{
    float seed[dst->rows * dst->cols];

    for (int j = 0; j < dst->rows * dst->cols; j++)
    {
        seed[j] = (float) rand() / (float) RAND_MAX;
    }

    for (int i = 0; i < dst->rows; i++)
    {
        for (int j = 0; j < dst->cols; j++)
        {
            float noise = 0.0;
            float scale = 1.0;
            float scale_acc = 0.0;
            for (int o = 0; o < n_octaves; o++)
            {
                int x_pitch = dst->cols >> o;
                int y_pitch = dst->rows >> o;
                int sample_x = (j / x_pitch) * x_pitch;
                int sample_y = (i / y_pitch) * y_pitch;
                int sample_x2 = (sample_x + x_pitch) % dst->cols;
                int sample_y2 = (sample_y + y_pitch) % dst->rows;

                float blend_x = (float) (j - sample_x) / (float) x_pitch;
                float blend_y = (float) (i - sample_y) / (float) y_pitch;
                float sample_1 = (1.0-blend_x) * seed[sample_y * dst->cols + sample_x] + blend_x * seed[sample_y * dst->cols + sample_x2];
                float sample_2 = (1.0-blend_x) * seed[sample_y2 * dst->cols + sample_x] + blend_x * seed[sample_y2 * dst->cols + sample_x2];
                
                noise += scale * (blend_y * (sample_2 - sample_1) + sample_1);
                scale_acc += scale;
                scale /= 2.0;
            }
            dst->data[(i * dst->cols) + j].rgb[0] = noise / scale_acc;
            dst->data[(i * dst->cols) + j].rgb[1] = noise / scale_acc;
            dst->data[(i * dst->cols) + j].rgb[2] = noise / scale_acc;
        }
    }
}
