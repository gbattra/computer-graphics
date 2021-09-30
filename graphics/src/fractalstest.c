/**
 * Bruce Maxwell
 * Greg Attra
 * 09/27/2021
 * 
 * Executable to test the Julia and Mandelbrot set program.
 */

/*Bruce A. MaxwellFall 2013  Creates a Mandelbrot set at a selected location*/

#include "image.h"
#include "fractals.h"


int main(int argc, char *argv[])
{
    Image *src;
    src = image_create(750, 1000);
    mandelbrot( src, -1.5, -1.5, 4);
    image_write( src, "output/lab2/mandelbrot-full.ppm");
    mandelbrot( src, 1.755, -0.02, 0.02);
    image_write( src, "output/lab2/mandelbrot.ppm");
    // julia( src, -1.8, -1.8*0.75, 3.6);

    julia( src, -1.5, -1.5, 4);
    image_write( src, "output/lab2/julia.ppm");
    image_free( src );
    return(0);
}