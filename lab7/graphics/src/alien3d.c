/**
 * Greg Attra
 * 11/12/2021
 * 
 * Alien abduction in 3D.
 */

#include "graphics.h"
#include <math.h>

static void draw_ground(Image *src, Matrix *vtm)
{
    Color grasslight = {64.0/255.0, 111.0/255.0, 0.0};
    Color grassdark = {14.0/255.0, 61.0/255.0, 0.0};

    Point corners[4];
    point_set2D(&corners[0], 0, src->rows / 2);
    point_set2D(&corners[1], src->cols, src->rows / 2);
    point_set2D(&corners[2], src->cols, src->rows);
    point_set2D(&corners[3], 0, src->rows);

    Polygon *ground;
    ground = polygon_createp(4, corners);
    polygon_drawFillG(ground, src, grasslight, grassdark, 1);
    polygon_free(ground);
}

static void draw_bg(Image *src, Matrix *vtm)
{
    Color white = {1.0, 1.0, 1.0};
    // draw bg
    Color skyblue = {11.0/255.0, 55.0/255.0, 66.0/255.0};
    for (int r = 0; r < src->rows; r++)
    {
        Line l;
        line_set2D(&l, 0, r, src->cols, r);
        line_draw(&l, src, skyblue);

        color_set(&skyblue, skyblue.c[0] + 0.0005, skyblue.c[1] + 0.0005, skyblue.c[2] + 0.0005);
    }

    // draw stars
    srand(0);
    double thresh = 0.2;
    for (int s = 0; s < src->rows; s++)
    {
        float random = (float) rand() / (float) RAND_MAX;
        while (random >= thresh)
        {
            float xrand = (float) rand() / (float) RAND_MAX;
            int x = (int) (xrand * (float) src->cols);
            image_setColor(src, s, x, white);

            random = (float) rand() / (float) RAND_MAX;
        }
        thresh += 0.001;
    }
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
    int frame = 20;
    rows = 600;
    cols = 900;

    float d = 15.0;
	point_set3D(&view.vrp, -15, 5, 20);
	vector_set( &(view.vpn), 20, -3, -35);
	vector_set( &(view.vup), 0.0, 1.0, 0.0 );
	view.d = 1.5;
	view.du = 1.0;
	view.dv = 1.0*rows/cols;
	view.screeny = rows;
	view.screenx = cols;
	view.f = 0.0;
	view.b = 3.0;

    int n_frames = 60;
    float dx = 0.6;
	matrix_setView3D( &VTM, &view );
	matrix_identity( &GTM );

    Image *src;
    src = image_create(rows, cols);

    float angle = 0.0;
    float da = 0.035;

    Module *bg = module_create();
    module_shadeMethod(bg, ShadeConstant);

    Color silobody = {199.0/255.0, 59.0/255.0, 52.0/255.0};
    Color silooutline = {silobody.c[0] + 0.2, silobody.c[1] + 0.2, silobody.c[2] + 0.2};
    Color silotop = {227.0/255.0, 202.0/255.0, 162.0/255.0};
    Color silotopoutline = {silotop.c[0] - 0.2, silotop.c[1] - 0.2, silotop.c[2] - 0.2};

    // draw barn
    module_identity(bg);
    module_rotateY(bg, cos(-0.25), sin(-0.25));
    module_scale(bg, 3.5, 2, 4);
    module_translate(bg, 0, 1.0, -10);
    module_color(bg, silobody);
    module_cube(bg, 1);
    module_color(bg, silooutline);
    module_cube(bg, 0);
    module_translate(bg, 0, 1.0, 0);
    module_color(bg, silotop);
    module_pyramid(bg, 1);
    module_color(bg, silotopoutline);
    module_pyramid(bg, 0);

    // draw silo
    module_identity(bg);
    module_translate(bg, -3.5, 0, -10);
    module_color(bg, silobody);
    module_scale(bg, 1, 4, 1);
    module_cylinder(bg, 20, 1);
    module_color(bg, silooutline);
    module_cylinder(bg, 20, 0);
    
    module_identity(bg);
    module_translate(bg, -3.5, 0, -10);
    module_translate(bg, 0, 4, 0);
    module_color(bg, silotop);
    module_hemisphere(bg, 3, 1);
    module_color(bg, silotopoutline);
    module_hemisphere(bg, 3, 0);

    float gtm_x = -dx * (((float) n_frames) / 2.0) - 2.0;
	for(frame=0;frame<n_frames;frame++) {
		char buffer[256];

        draw_bg(src, &VTM);
        draw_ground(src, &VTM);

	    matrix_identity( &GTM );
        // draw bg
        module_draw(bg, &VTM, &GTM, &ds, NULL, src);

        Module *m = module_create();
        module_shadeMethod(m, ShadeConstant);
        matrix_translate(&GTM, gtm_x, 0, 0);

        // // draw beam
        module_color(m, beam);
		module_rotateY(m, cos(angle), sin(angle));
        module_scale(m, 1.5, 3, 1.5);
        module_cone(m, 3, 1);
        Color beamdark = {beam.c[0] - .2, beam.c[1] - .2, beam.c[2] - .2};
        module_color(m, beamdark);
        module_cone(m, 3, 0);
        
        // draw body
        module_identity(m);
		module_rotateY(m, cos(angle), sin(angle));
        module_color(m, body);
        module_scale(m, 2, 0.35, 2);
        module_translate(m, 0, 3.0, 0);
        module_sphere(m, 3, 1);
        Color bodylight = {body.c[0] + .2, body.c[1] + .2, body.c[2] + .2};
        module_color(m, bodylight);
        module_sphere(m, 3, 0);

        // // draw top
        module_identity(m);
		module_rotateY(m, cos(angle), sin(angle));
        module_color(m, window);
        module_scale(m, .85, 0.85, .85);
        module_translate(m, 0, 3.2, 0);
        module_hemisphere(m, 4, 1);
        Color windowdark = {body.c[0] - .2, body.c[1] - .2, body.c[2] - .2};
        module_color(m, windowdark);
        module_hemisphere(m, 4, 0);

        module_draw(m, &VTM, &GTM, &ds, NULL, src);

        module_delete(m);

		sprintf(buffer, "output/lab7/alien/alien_frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);

        angle += da;
        gtm_x += dx;
    }
    return 0;
}
