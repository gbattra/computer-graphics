/**
 * Greg Attra
 * 10/19/2021
 * 
 * Executable to create a 3D scene.
 */

#include "graphics.h"

int frame = 0;

static void draw_cubes(Image *src, Matrix *vtm)
{
    int nCubes = 3;
    Color cols[nCubes*nCubes];

    double delta = 1;
    double x, y, z;
    x = 0;
    y = 0;
    z = 0;

    srand(0);
    for (int c = 0; c < nCubes * nCubes; c++) color_random(&cols[c]);

    for (int i = 0; i < nCubes; i++)
    {
        for (int j = 0; j < nCubes; j++)
        {
            // printf("%i - %i\n", i, j);
            Color colors[6] = {cols[j], cols[j], cols[j], cols[j], cols[j], cols[j]};

            Point cp;
            point_set3D(&cp, x, y, z);

            Cube *cube;
            cube = cube_create(1, 1, 1, cp);
            matrix_xformCube(vtm, cube);
            cube_normalize(cube);
            cube_draw(cube, src, colors);
            cube_free(cube);

            x += delta;
        }
        z += 2;
        x = 0;
        // y += delta;
    }
}

int main(int argc, char *argv[])
{
    char filename[256];
    int nframes = 20;
    int rows = 600;
    int cols = 900;
    View3D view;
    Image *src;
    src = image_create(rows, cols);

    for (int i = 0; i < nframes; i++)
    {
        frame = i;
        double alpha = ((double) i) / 10.0;
        point_set( &(view.vrp), 3*alpha, 2*alpha, -2*alpha - (1.0-alpha)*3, 1.0 );
        vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );

        vector_set( &(view.vup), 0, 1, 0 );
        view.d = 1;
        view.du = 2;
        view.dv = view.du * ((float) rows / (float) cols);
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
