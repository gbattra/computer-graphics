/**
 * Greg Attra
 * 09/21/2021
 * 
 * Executable for testing perlin noise.
 */

#include "image.h"
#include "noise.h"

/**
 * Entrypoint for executable.
 */
int main(int argc, char *argv[])
{
    Image *src;
    src = image_create(600, 1000);
    perlin(src, 9);
    image_write(src, "output/lab2/perlin.ppm");

    image_free(src);
}
