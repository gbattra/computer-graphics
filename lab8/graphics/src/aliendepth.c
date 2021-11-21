/**
 * Greg Attra
 * 11/18/2021
 * 
 * Example of the depth rendering with z-buffer logic.
 */

#include "graphics.h"
#include <math.h>


int main(int argc, char *argv[])
{
    Color beam = {247.0/255.0, 227.0/255.0, 171.0/255.0};
    Color body = {29.0/255.0, 32.0/255.0, 43.0/255.0};
    Color window = {183.0/255.0, 186.0/255.0, 196.0/255.0};
    Color red = {1, 0, 0};

    Image *src;
    Matrix VTM;
    Matrix GTM;
    int rows = 800;
    int cols = 1200;
    int i;

    Color Grey;
    Color Yellow;
    Color Blue;

    DrawState *ds;
    View3D view;

    color_set( &Grey, 175/255.0, 178/255.0, 181/255.0 );
    color_set( &Yellow, 240/255.0, 220/255.0, 80/255.0 );
    color_set( &Blue, 50/255.0, 60/255.0, 200/255.0 );

    src = image_create(rows, cols);

    matrix_identity(&GTM);
    matrix_identity(&VTM);

    float d = 15.0;
    point_set3D(&(view.vrp), d, 3.0, d);
    vector_set(&(view.vpn), -d, -1, -d);
    vector_set(&(view.vup), 0.0, 1.0, 0.0);
    view.d = 2.0;
    view.du = 1.0;
	view.dv = 1.0*rows/cols;
    view.f = 0.0;
    view.b = 35;
    view.screenx = cols;
    view.screeny = rows;
    matrix_setView3D(&VTM, &view);

    ds = drawstate_create();
    ds->shade = ShadeDepth;

    for(i=0;i<36*2;i++) {
        char buffer[256];

        image_reset( src );

        matrix_identity(&GTM);
        matrix_rotateY(&GTM, cos(i*2*M_PI/(36.0*2)), sin(i*2*M_PI/(36.0*2)));

        Module *m = module_create();

        // draw beam
        module_color(m, beam);
        module_scale(m, 1.5, 3, 1.5);
        module_cone(m, 3, 1);
        
        // draw body
        module_identity(m);
        module_color(m, body);
        module_scale(m, 2, 0.35, 2);
        module_translate(m, 0, 3.0, 0);
        module_sphere(m, 3, 1);

        // // // draw top
        module_identity(m);
        module_color(m, window);
        module_scale(m, .85, 0.85, .85);
        module_translate(m, 0, 3.2, 0);
        module_hemisphere(m, 4, 1);

        // draw lights
        module_identity(m);
        module_color(m, red);
        module_scale(m, 0.15, 0.15, 0.15);
        module_translate(m, 1, 3.2, 1);
        module_sphere(m, 3, 1);

        module_identity(m);
        module_color(m, red);
        module_scale(m, 0.15, 0.15, 0.15);
        module_translate(m, -1, 3.2, 1);
        module_sphere(m, 3, 1);

        module_identity(m);
        module_color(m, red);
        module_scale(m, 0.15, 0.15, 0.15);
        module_translate(m, 1, 3.2, -1);
        module_sphere(m, 3, 1);

        module_identity(m);
        module_color(m, red);
        module_scale(m, 0.15, 0.15, 0.15);
        module_translate(m, -1, 3.2, -1);
        module_sphere(m, 3, 1);

        // pillar
        module_identity(m);
        module_color(m, window);
        module_scale(m, 0.5, 4, 0.5);
        module_translate(m, 5, 0, 0);
        module_cylinder(m, 15, 1);

        // pillar
        module_identity(m);
        module_color(m, window);
        module_scale(m, 0.5, 4, 0.5);
        module_translate(m, -5, 0, 0);
        module_cylinder(m, 15, 1);

        // pillar
        module_identity(m);
        module_color(m, window);
        module_scale(m, 0.5, 4, 0.5);
        module_translate(m, 0, 0, 5);
        module_cylinder(m, 15, 1);

        // pillar
        module_identity(m);
        module_color(m, window);
        module_scale(m, 0.5, 4, 0.5);
        module_translate(m, 0, 0, -5);
        module_cylinder(m, 15, 1);

        module_draw(m, &VTM, &GTM, ds, NULL, src);

        module_delete( m );

        sprintf(buffer, "output/lab8/aliendepth/frame-%03d.ppm", i);
        image_write(src, buffer);
    }

    image_free( src );


    return(0);
}
