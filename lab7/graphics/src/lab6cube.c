/**
 * Greg Attra
 * 10/30/2021
 * 
 * Executable for demoing the module_cube function.
 */

#include "graphics.h"
#include <math.h>


int main(int argc, char *argv[])
{
    int rows = 360;
    int cols = 640;
    Matrix vtm, gtm;
    View3D view;
    point_set3D( &(view.vrp), 10, 10, 10);
    vector_set( &(view.vpn), -9, -10, -12);
    vector_set( &(view.vup), 0, 1, 0 );
    view.d = 1;
    view.du = 10.0 / 20.0;
    view.dv = view.du * ((float) rows / (float) cols);
    view.f = 0;
    view.b = 50;
    view.screenx = 640;
    view.screeny = 360;

    matrix_setView3D( &vtm, &view );
    matrix_identity( &gtm );

    Module *cube = module_create();
    module_scale(cube, 1.5, 1.5, 1.5);
    module_rotateY(cube, cos(.5), sin(.5));
    module_cube(cube, 1);

    module_identity(cube);
    module_scale(cube, 1.5, 1.5, 1.5);
    module_translate(cube, 3, 0, -2);
    module_rotateY(cube, cos(.1), sin(.1));
    module_cube(cube, 1);

    Image *src;
    src = image_create(rows, cols);

    DrawState *ds = drawstate_create();
    ds->shade = ShadeFrame;

    Color blue = {0.0, 0.0, 1.0};

    Module *scene = module_create();
    module_color(scene, blue);
    module_module(scene, cube);
    module_draw(scene, &vtm, &gtm, ds, NULL, src);

    image_write(src, "output/lab6/cube.ppm");

    image_free(src);
    module_delete(cube);

    return 0;
}