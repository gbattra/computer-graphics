/**
 * Greg Attra
 * 12/07/2021
 * 
 * Test exec for the Barycentric fill update.
 */

#include "graphics.h"


int main(int argc, char *argv[])
{
    int rows, cols;
    Matrix VTM, GTM;
    Color White, Grey,DkGrey;
    DrawState *ds;
    View3D view;
    Lighting *light;

    rows = 900;
    cols = 900;

    color_set( &White, 1.0, 1.0, 1.0 );
    color_set( &Grey, 0.6, 0.62, 0.64 );
    color_set( &DkGrey, 0.1, 0.1, 0.1 );

	float d = 5.0;
	point_set3D(&view.vrp, d, d, d);
	vector_set( &(view.vpn), -d, -d, -d);
	vector_set( &(view.vup), 0.0, 1.0, 0.0 );
	view.d = 1.5;
	view.du = 1.0;
	view.dv = 1.0*rows/cols;
	view.screeny = rows;
	view.screenx = cols;
	view.f = 0.0;
	view.b = 3.0;

    matrix_setView3D( &VTM, &view );
    matrix_identity( &GTM );

    ds = drawstate_create();
    point_copy(&ds->viewer, &(view.vrp));
    ds->shade = ShadeGouraud;
    ds->fill = BarycentricFill;

    light = lighting_create();
    lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
    
    Image *src;
    src = image_create(rows, cols);

    Module *md;
    md = module_create();

    module_color(md, White);
    module_bodyColor(md, White);
    module_surfaceColor(md, DkGrey);
    module_cube(md, 1);
    module_draw(md, &VTM, &GTM, ds, light, src);
    module_delete(md);
    
    image_write(src, "test10a.c");
    image_free(src);

    return 0;
}