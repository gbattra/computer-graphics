/**
 * Greg Attra
 * 11/10/2021
 * 
 * Executable demoing the cone functionality.
 */

#include "graphics.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    Color white = {1, 1, 1};
	DrawState ds;
    View3D view;
    int rows, cols;
    Matrix VTM, GTM;
    int frame = 20;
    rows = 600;
    cols = 900;

    point_set3D(&(view.vrp), 5, 5, 5 );
	vector_set( &(view.vpn), -5, -4.5, -5 );
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

    Module *m = module_create();
	module_shadeMethod(m, ShadeConstant);
    module_color(m, white);
    module_scale(m, 1.0, 1.5, 1.0);
    module_cone(m, 1, 0);
    module_translate(m, 2, 0, 1);
    module_cone(m, 1, 1);

	// Create the animation by adjusting the GTM
	for(frame=0;frame<60;frame++) {
		char buffer[256];
		matrix_rotateY(&GTM, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( m, &VTM, &GTM, &ds, NULL, src );

		sprintf(buffer, "output/lab7/cone/cone_frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

    image_free(src);
    module_delete(m);

    return 0;
}
