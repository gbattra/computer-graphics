/**
 * Greg Attra
 * 09/21/2021
 * 
 * Program to generate a composite image given a foreground, background and a mask.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ppmIO.h>

/**
 * String describing program usage.
 */
char *usage_str =
    "Usage:\n"
    "> composite <foreground ppm image> <background ppm image> <mask ppm file> <output ppm file>";

/**
 * Reads in the foreground, background and mask images, and builds a composite.
 * 
 * @param argc arg count
 * @param argv arg pointers
 * 
 * @return 0 success, -1 fail
 */
int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        printf(usage_str);
        exit(-1);
    }

    int dx = 0;
    int dy = 0;
    if (argc == 7)
    {
        dx = atoi(argv[5]);
        dy = atoi(argv[6]);
    }

    Pixel *fg_img;
    int fg_rows, fg_cols, fg_colors;
    fg_img = readPPM(&fg_rows, &fg_cols, &fg_colors, argv[1]);
    if (!fg_img)
    {
        fprintf(stderr, "Unable to read %s\n", argv[1]);
        exit(-1);
    }
    long fg_imagesize = (long) fg_rows * (long) fg_cols;

    Pixel *bg_img;
    int bg_rows, bg_cols, bg_colors;
    bg_img = readPPM(&bg_rows, &bg_cols, &bg_colors, argv[2]);
    if (!bg_img)
    {
        fprintf(stderr, "Unable to read %s\n", argv[2]);
        exit(-1);
    }
    long bg_imagesize = (long) bg_rows * (long) bg_cols;

    Pixel *mask_img;
    int mask_rows, mask_cols, mask_colors;
    mask_img = readPPM(&mask_rows, &mask_cols, &mask_colors, argv[3]);
    if (!mask_img)
    {
        fprintf(stderr, "Unable to read %s\n", argv[3]);
        exit(-1);
    }
    for (int r = 0; r < fg_rows; r++)
    {
        if (r >= bg_rows) break;
        
        Pixel *bg_row = &bg_img[(r + dy) * bg_cols];
        Pixel *fg_row = &fg_img[r * fg_cols];
        Pixel *mask_row = &mask_img[r * mask_cols];

        for (int c = 0; c < fg_cols; c++)
        {
            if (c >= bg_cols) break;

            Pixel *bg_pix = &bg_row[c + dx];
            Pixel *fg_pix = &fg_row[c];
            Pixel *mask_pix = &mask_row[c];

            float alpha = ((mask_pix->r / 255)
                         + (mask_pix->g / 255)
                         + (mask_pix->b/ 255)) / 3;

            int r = (alpha * fg_pix->r) + ((1 - alpha) * bg_pix->r);
            int g = (alpha * fg_pix->g) + ((1 - alpha) * bg_pix->g);
            int b = (alpha * fg_pix->b) + ((1 - alpha) * bg_pix->b);

            bg_pix->r = r;
            bg_pix->g = g;
            bg_pix->b = b;
        }
    }

    writePPM(bg_img, bg_rows, bg_cols, bg_colors, argv[4]);

    free(fg_img);
    free(bg_img);
    free(mask_img);
    
    return 0;
}
