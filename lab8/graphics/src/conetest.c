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

	int divisions = 0;
	if(argc > 1) {
		int tmp = atoi(argv[1]);
		if( tmp >= 0 && tmp < 10 )
			divisions = tmp;
	}
    float d = 15.0;
	point_set3D(&view.vrp, 1, d, 0);
	vector_set( &(view.vpn), -1, -d, 0);
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

    float angle = 0.0;
    float da = 0.1;

	for(frame=0;frame<1;frame++) {
		char buffer[256];
		Module *m = module_create();
		module_shadeMethod(m, ShadeConstant);
		module_color(m, white);

		module_rotateY(m, cos(angle), sin(angle));
		module_rotateX(m, cos(angle), sin(angle));
		module_cone(m, divisions, 0);

		// module_identity(m);
		// module_rotateY(m, cos(angle), sin(angle));
		// module_rotateX(m, cos(angle), sin(angle));
		// module_translate(m, 2, 0, 0);
		// module_cone(m, divisions, 1);
		
		// module_identity(m);
		// module_rotateY(m, cos(angle), sin(angle));
		// module_rotateX(m, cos(angle), sin(angle));
		// module_translate(m, 4, 0, 0);
		// module_cone(m, divisions, 0);

		// module_identity(m);
		// module_rotateY(m, cos(angle), sin(angle));
		// module_rotateX(m, cos(angle), sin(angle));
		// module_translate(m, 6, 0, 0);
		// module_cone(m, divisions, 1);

		module_draw( m, &VTM, &GTM, &ds, NULL, src );

    	module_delete(m);

		sprintf(buffer, "output/lab7/cone/cone_frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);

        angle += da;
	}

    image_free(src);

    return 0;
}
