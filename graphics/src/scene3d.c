/**
 * Greg Attra
 * 10/19/2021
 * 
 * Executable to create a 3D scene.
 */

#include "graphics.h"

static void draw_cube(
    Image *src, Matrix *vtm,
    double h, double w, double l,
    double x, double y, double z)
{

}

static void draw_cubes(Image *src, Matrix *vtm, Color *cols)
{
    double w = 5.0;
    double l = 5.0;
    double maxHeight = 5.0;
    int nCubes = 10;
    for (int i = 0; i < nCubes; i++)
    {
        double h = (((float) rand()) / (float) RAND_MAX) * maxHeight;
    }

}

int main(int argc, char *argv[])
{
    char filename[256];
    int nframes = 40;
    int rows = 900;
    int cols = 1200;
    Image *src;
    src = image_create(rows, cols);

    double dx = 15.0;
    Point vrp;
    point_set2D(&vrp, 2.0, 10.0);
    Vector x_axis;
    vector_set(&x_axis, 1.0, 0.0, 0.0);

    double pan_step = 0.5;
    double zoom_step = 1;

    for (int i = 0; i < nframes; i++)
    {
        
    }

    return 0;
}
