/**
 * Greg Attra
 * 12/08/2021
 * 
 * Test the counter gravity force on a rigidbody.
 */

#include "graphics.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    float friction = atof(argv[1]);
    if( friction < 0 || friction > 1 )
        return 1;

    int rows, cols, nFrames;
    Matrix VTM, GTM;
    Color White, Grey,DkGrey;
    DrawState *ds;
    View3D view;
    Lighting *light;

    rows = 900;
    cols = 900;
    nFrames = 40;

    color_set( &White, 1.0, 1.0, 1.0 );
    color_set( &Grey, 0.6, 0.62, 0.64 );
    color_set( &DkGrey, 0.1, 0.1, 0.1 );

	float d = 25;
	point_set3D(&view.vrp, d/3.5, 0, d);
	vector_set( &(view.vpn), 0, 0, -d);
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
    // ds->shade = ShadeFlat;
    ds->fill = BarycentricFill;

    light = lighting_create();
    lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
    
    Image *src;
    src = image_create(rows, cols);

    Rigidbody *rb = rigidbody_create();
    rigidbody_setMass(rb, 1);
    rigidbody_setUseGravity(rb, 0);
    rigidbody_setFriction(rb, friction);

    Vector fdir;
    vector_set(&fdir, 1, 0, 0);
    Force *f = force_createp(&fdir, 30);
    rigidbody_addForce(rb, f);

    for (int i = 0; i < nFrames; i++)
    {
        Module *md;
        md = module_create();

        Module *sphere;
        sphere = module_create();
        module_color(sphere, White);
        module_bodyColor(sphere, White);
        module_surfaceColor(sphere, DkGrey);
        module_sphere(sphere, 4, 1);
        rigidbody_setModule(rb, sphere);

        rigidbody_tick(rb);
        rigidbody_render(rb, md);

        module_draw(md, &VTM, &GTM, ds, light, src);
        module_delete(md);

        char buffer[256];
        if (friction > 0)
            sprintf(buffer, "final/testfrictionon/frictionon_frame%03d.ppm", i);
        else 
            sprintf(buffer, "final/testfrictionoff/frictionoff_frame%03d.ppm", i);
        image_write(src, buffer);

        image_reset(src);
    }

    rigidbody_free(rb);
    image_free(src);

    return 0;
}