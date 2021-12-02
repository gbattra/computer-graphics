/**
 * Greg Attra
 * 11/30/2021
 * 
 * Executable for testing Gouraud shading on simple cube.
 */

#include "graphics.h"


int main(int argc, char *argv[])
{
    Image *src;
    Lighting *l;
    Point lp;
    Color ambient, point, gray;
    DrawState *ds;
    Module *m;
    View3D view;
    Matrix GTM, VTM;
    int rows = 600;
    int cols = 600;

	color_set(&ambient, 0.2, 0.25, 0.3);
	color_set(&gray, 0.2, 0.25, 0.3);
	color_set(&point, 0.9, 0.85, 0.8);

    matrix_identity(&GTM);
    matrix_identity(&VTM);

    point_set3D(&(view.vrp), 2, 2, 2);
    vector_set(&(view.vpn), -2, -2, -2);
    vector_set(&(view.vup), 0.0, 1.0, 0.0);
    view.d = 2.0;
    view.du = 1.0;
    view.dv = 1.0;
    view.f = 0.0;
    view.b = 50;
    view.screenx = cols;
    view.screeny = rows;
    matrix_setView3D(&VTM, &view);

    l = lighting_create();
    lighting_add( l, LightAmbient, &ambient, NULL, NULL, 0.0, 0.0 );
    point_set3D(&lp, 3, 2, 3);
    lighting_add( l, LightPoint, &point, NULL, &lp, 0.0, 0.0 );

    ds = drawstate_create();
    ds->shade = ShadeConstant;
    ds->surfaceCoeff = 10;
    color_copy(&ds->color, &gray);
    
    m = module_create();
    module_cube(m, 1);

    src = image_create(600, 600);

    module_draw(m, &VTM, &GTM, ds, l, src);

    module_delete(m);

    image_write(src, "output/lab9/gouraud.ppm");
    image_free(src);

    return 0;
}