/**
 * Greg Attra
 * 10/19/2021
 * 
 * Executable to create a 3D scene.
 */

#include "graphics.h"

static void draw_cubes(Image *src, Matrix *vtm)
{
    double w = 1.0;
    double l = 1.0;
    double maxHeight = 1.0;
    int nCubes = 1;
    Color cols[nCubes];

    srand(0);
    for (int c = 0; c < nCubes; c++) color_random(&cols[c]);

    for (int i = 0; i < nCubes; i++)
    {
        Color colors[6] = {cols[i], cols[i], cols[i], cols[i], cols[i], cols[i]};

        double h = (((float) rand()) / (float) RAND_MAX) * maxHeight;
        Point c;
        point_set3D(&c, 0, 0, 0);

        Cube *cube;
        cube = cube_create(h, w, l, c);
        matrix_xformCube(vtm, cube);
        cube_draw(cube, src, colors);
        cube_free(cube);
    }
}

int main(int argc, char *argv[])
{
    char filename[256];
    int nframes = 1;
    int rows = 600;
    int cols = 900;
    View3D view;
    Image *src;
    src = image_create(rows, cols);

    for (int i = 0; i < nframes; i++)
    {
        double alpha = ((double) i) / 10.0;
        point_set( &(view.vrp), 1, 1, 1, 1.0 );
        vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );

        vector_set( &(view.vup), 0, 1, 0 );
        view.d = 1;
        view.du = 10;
        view.dv = view.du * (float) rows / cols;
        view.f = 0;
        view.b = 4;
        view.screenx = cols;
        view.screeny = rows;

        Matrix vtm;
        matrix_setView3D( &vtm, &view );

        image_reset(src);
        draw_cubes(src, &vtm);

        sprintf(filename, "output/lab5/scene3D/frame-%04d.ppm", i);
        image_write(src, filename);
    }

    image_free(src);

    return 0;
}
