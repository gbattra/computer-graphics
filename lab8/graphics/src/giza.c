/**
 * Greg Attra
 * 11/12/2021
 * 
 * Pyramids at Giza.
 */

#include "graphics.h"
#include <math.h>

static void add_pmd(Module *m, Pyramid *pmd)
{
    Color py_front = {232.0/255.0, 191.0/255.0, 123.0/255.0};
    Color py_back = {89.0/255.0, 68.0/255.0, 33.0/255.0};
    Color py_side_light = {212.0/255.0, 171.0/255.0, 102.0/255.0};
    Color py_side_dark = {150.0/255.0, 119.0/255.0, 66.0/255.0};

    module_color(m, py_front);
    module_polygon(m, &pmd->faces[0]);
    module_color(m, py_side_light);
    module_polygon(m, &pmd->faces[1]);
    module_color(m, py_side_dark);
    module_polygon(m, &pmd->faces[2]);
    module_color(m, py_back);
    module_polygon(m, &pmd->faces[3]);
}

int main(int argc, char *argv[])
{
    Color beam = {247.0/255.0, 227.0/255.0, 171.0/255.0};
    Color body = {29.0/255.0, 32.0/255.0, 43.0/255.0};
    Color window = {183.0/255.0, 186.0/255.0, 196.0/255.0};

	DrawState ds;
    View3D view;
    int rows, cols;
    Matrix VTM, GTM;
    rows = 600;
    cols = 900;

    float d = 30.0;
	point_set3D(&view.vrp, -d, d, d/4.0);
	vector_set( &(view.vpn), d, -d, -d/4.0);

	// point_set3D(&view.vrp, 1, 100, 0);
	// vector_set( &(view.vpn), -1, -100, 0);

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

    Image *src;
    src = image_create(rows, cols);

    Point cp;
    point_set3D(&cp, 0, 0, 0);
    Pyramid *pmd = pyramid_create(&cp, 1.0, 1.0, 1.0);

    Module *m = module_create();
    module_shadeMethod(m, ShadeConstant);

    module_identity(m);
    module_scale(m, 4, 4, 4);
    add_pmd(m, pmd);

    module_identity(m);
    module_scale(m, 4, 4, 4);
    module_translate(m, 6, 0, 6);
    add_pmd(m, pmd);

    module_scale(m, 0.25, 0.25, 0.25);
    module_translate(m, -1.5, 3, -1.5);
    add_pmd(m, pmd);

    module_identity(m);
    module_scale(m, 2, 2, 2);
    module_translate(m, -5, 0, -4);
    add_pmd(m, pmd);

    module_scale(m, 0.35, 0.35, 0.35);
    module_translate(m, -5, 0, -4);
    add_pmd(m, pmd);

    module_translate(m, 0, 0, 1);
    add_pmd(m, pmd);

    module_translate(m, 0, 0, 1);
    add_pmd(m, pmd);

    BezierSurface road;
    bezierSurface_init(&road);
    road.vlist[0].val[0] += 10.0;
    road.vlist[4].val[0] += 10.0;
    road.vlist[8].val[0] += 10.0;
    road.vlist[12].val[0] += 10.0;

    road.vlist[1].val[0] -= 10.0;
    road.vlist[5].val[0] -= 10.0;
    road.vlist[9].val[0] -= 10.0;
    road.vlist[13].val[0] -= 10.0;

    road.vlist[2].val[0] += 10.0;
    road.vlist[6].val[0] += 10.0;
    road.vlist[10].val[0] += 10.0;
    road.vlist[14].val[0] += 10.0;
    
    Color roadcolor = {0.25, 0.25, 0.25};
    module_identity(m);
    module_scale(m, 0.15, 0, 25);
    module_rotateY(m, cos((M_PI/2.0) * 1.5), sin(M_PI/2.0) * 1.5);
    module_translate(m, -10, 0, 10);
    module_color(m, roadcolor);
    module_bezierSurface(m, &road, 3, 1);

    int n_frames = 60;
    float angle = 0.0;
    float da = 0.05;
    float dx = 0.5;
    float dz = 0.5;
    float gtm_x = -20.0;
    float gtm_z = -10.0;
	for(int frame=0;frame<n_frames;frame++) {
		char buffer[256];

        image_fillrgb(src, 181.0/255.0, 155.0/255.0, 110.0/255.0);

        matrix_identity(&GTM);
        module_draw(m, &VTM, &GTM, &ds, NULL, src);

        Module *alien = module_create();
        module_shadeMethod(alien, ShadeConstant);
        matrix_translate(&GTM, gtm_x, 0, gtm_z);

        // // draw beam
        module_color(alien, beam);
		module_rotateY(alien, cos(angle), sin(angle));
        module_scale(alien, 1.5, 3, 1.5);
        module_cone(alien, 3, 1);
        Color beamdark = {beam.c[0] - .2, beam.c[1] - .2, beam.c[2] - .2};
        module_color(alien, beamdark);
        module_cone(alien, 3, 0);
        
        // draw body
        module_identity(alien);
		module_rotateY(alien, cos(angle), sin(angle));
        module_color(alien, body);
        module_scale(alien, 2, 0.35, 2);
        module_translate(alien, 0, 3.0, 0);
        module_sphere(alien, 3, 1);
        Color bodylight = {body.c[0] + .2, body.c[1] + .2, body.c[2] + .2};
        module_color(alien, bodylight);
        module_sphere(alien, 3, 0);

        // // draw top
        module_identity(alien);
		module_rotateY(alien, cos(angle), sin(angle));
        module_color(alien, window);
        module_scale(alien, .85, 0.85, .85);
        module_translate(alien, 0, 3.2, 0);
        module_hemisphere(alien, 4, 1);
        Color windowdark = {body.c[0] - .2, body.c[1] - .2, body.c[2] - .2};
        module_color(alien, windowdark);
        module_hemisphere(alien, 4, 0);

        module_draw(alien, &VTM, &GTM, &ds, NULL, src);
        module_delete(alien);

		sprintf(buffer, "output/lab7/giza/giza_frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);

        angle += da;
        gtm_x += dx;
        gtm_z += dz;
    }
    module_delete(m);
    image_free(src);
    
    return 0;
}