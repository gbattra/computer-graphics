/**
 * Greg Attra
 * 09/23/2021
 * 
 * Implementation of the image API defined in image.h
 */

#include "image.h"
#include "ppmIO.h"
#include <stdio.h>
#include <stdlib.h>

Image* image_create(int rows, int cols)
{
    Image *img = (Image *) malloc(sizeof(Image));
    image_alloc(img, rows, cols);

    return img;
}

void image_init(Image *src)
{
    src->rows = 0;
    src->cols = 0;
    src->data = NULL;
}

void image_free(Image *src)
{
    free(src->data);
    free(src);
}

int image_alloc(Image *src, int rows, int cols)
{
    src->rows = rows;
    src->cols = cols;
    src->data = (FPixel*) malloc(sizeof(FPixel) * rows * cols);
    return 0;
}

void image_dealloc(Image *src)
{
    free(src->data);
    image_init(src);
}

int image_write(Image *src, char *filename)
{
    Pixel *img = (Pixel *) malloc(sizeof(Pixel) * src->rows * src->cols);
    for (int i = 0; i < (src->rows * src->cols); i++)
    {
        int r = (int) (src->data[i].rgb[0] * 255.0);
        int g = (int) (src->data[i].rgb[1] * 255.0);
        int b = (int) (src->data[i].rgb[2] * 255.0);
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        img[i].r = (unsigned char) r;
        img[i].g = (unsigned char) g;
        img[i].b = (unsigned char) b;
    }

    writePPM(img, src->rows, src->cols, 255, filename);
    free(img);

    return 0;
}

Image* image_read(char *filename)
{
    Image *img = (Image *) malloc(sizeof(Image));
    Pixel *src;
    int colors;
    src = readPPM(&img->rows, &img->cols, &colors, filename);
    img->data = (FPixel *) malloc(sizeof(FPixel) * img->rows * img->cols);
    for (int i = 0; i < (img->rows * img->cols); i++)
    {
        img->data[i].rgb[0] = ((float) src[i].r) / 255.0;
        img->data[i].rgb[1] = ((float) src[i].g) / 255.0;
        img->data[i].rgb[2] = ((float) src[i].b) / 255.0;
    }

    free(src);

    return img;
}

float image_getc(Image *src, int i, int j, int c)
{
    return src->data[(i * src->cols) + j].rgb[c];   
}

float image_geta(Image *src, int i, int j)
{
    return src->data[(i * src->cols) + j].a;
}

float image_getz(Image *src, int i, int j)
{
    return src->data[(i * src->cols) + j].z;
}

void image_setf(Image *src, int i, int j, FPixel val)
{
    if (i < 0 || i >= src->rows || j < 0 || j >= src->cols) return;

    FPixel *pix = &src->data[(i * src->cols) + j];
    pix->rgb[0] = val.rgb[0];
    pix->rgb[1] = val.rgb[1];
    pix->rgb[2] = val.rgb[2];
    pix->a = val.a;
    pix->z = val.z;
}

void image_seta(Image *src, int i, int j, float val)
{
    src->data[(i * src->cols) + j].a = val;
}

void image_setz(Image *src, int i, int j, float val)
{
    src->data[(i * src->cols) + j].z = val;
}

void image_setc(Image *src, int i, int j, int c, float value)
{
    FPixel *pix = &src->data[(i * src->cols) + j];
    pix->rgb[c] = value;
}

void image_reset(Image *src)
{
    for (int i = 0; i < src->rows; i++)
    {
        for (int j = 0; j < src->cols; j++)
        {
            FPixel *pix = &src->data[(i * src->cols) + j];
            pix->a = 1.0;
            pix->z = 1.0;
            pix->rgb[0] = 0.0;
            pix->rgb[1] = 0.0;
            pix->rgb[2] = 0.0;
        }
    }
}

void image_fill(Image *src, FPixel val)
{
    for (int i = 0; i < src->rows; i++)
    {
        for (int j = 0; j < src->cols; j++)
        {
            FPixel *pix = &src->data[(i * src->cols) + j];
            pix->a = val.a;
            pix->z = val.z;
            pix->rgb[0] = val.rgb[0];
            pix->rgb[1] = val.rgb[1];
            pix->rgb[2] = val.rgb[2];
        }
    }
}

void image_fillrgb(Image *src, float r, float g, float b)
{
    for (int i = 0; i < src->rows; i++)
    {
        for (int j = 0; j < src->cols; j++)
        {
            FPixel *pix = &src->data[(i * src->cols) + j];
            pix->rgb[0] = r;
            pix->rgb[1] = g;
            pix->rgb[2] = b;
        }
    }
}

void image_filla(Image *src, float a)
{
    for (int i = 0; i < src->rows; i++)
    {
        for (int j = 0; j < src->cols; j++)
        {
            FPixel *pix = &src->data[(i * src->cols) + j];
            pix->a = a;
        }
    }
}

void image_fillz(Image *src, float z)
{
    for (int i = 0; i < src->rows; i++)
    {
        for (int j = 0; j < src->cols; j++)
        {
            FPixel *pix = &src->data[(i * src->cols) + j];
            pix->z = z;
        }
    }
}

void color_copy(Color *to, Color *from)
{
    to->c[0] = from->c[0];
    to->c[1] = from->c[1];
    to->c[2] = from->c[2];
}

void color_set(Color *to, float r, float g, float b)
{
    to->c[0] = r;
    to->c[1] = g;
    to->c[2] = b;
}

void image_setColor(Image *src, int i, int j, Color val)
{
    if (i < 0 || i >= src->rows || j < 0 || j > src->cols) return;
    FPixel *pix = &src->data[(i * src->cols) + j];
    pix->rgb[0] = val.c[0];
    pix->rgb[1] = val.c[1];
    pix->rgb[2] = val.c[2];
}

Color image_getColor(Image *src, int i, int j)
{
    Color color;
    FPixel *pix = &src->data[(i * src->cols) + j];
    color.c[0] = pix->rgb[0];
    color.c[1] = pix->rgb[1];
    color.c[2] = pix->rgb[2];

    return color;
}

int color_compare(Color *one, Color *two)
{
    if (one->c[0] == two->c[0]
        && one->c[1] == two->c[1]
        && one->c[2] == two->c[2])
    {
        return 0;
    }
    return 1;
}

void color_print(Color *color, FILE *fp)
{
    fprintf(fp, "[ %f, %f, %f ]\n", color->c[0], color->c[1], color->c[2]);
}

void color_interpolate(Color *target, Color *start, Color *end, double alpha)
{
    target->c[0] = (1.0 - alpha) * start->c[0] + alpha * end->c[0];
    target->c[1] = (1.0 - alpha) * start->c[1] + alpha * end->c[1];
    target->c[2] = (1.0 - alpha) * start->c[2] + alpha * end->c[2];
}

void color_random(Color *target)
{
    color_set(
        target,
        ((float) rand()) / (float) RAND_MAX,
        ((float) rand()) / (float) RAND_MAX,
        ((float) rand()) / (float) RAND_MAX);
}
