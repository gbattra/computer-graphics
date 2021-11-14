/**
 * Greg Attra
 * 10/31/2021
 * 
 * Excutable to generate a 3D restaurant.
 */

#include "graphics.h"
#include <math.h>


static void chair(Module *md)
{
    float h = 6;
    float w = 3;
    float l = 3;
    float thickness = 0.25;

    Module *chair = module_create();
    Color chairColor = {1.0, 1.0, 1.0};
    module_color(chair, chairColor);

    // seat
    module_scale(chair, w, thickness, l - thickness);
    module_cube(chair, 0);

    // legs
    module_identity(chair);
    module_scale(chair, thickness, h/2.0 - thickness, thickness);
    module_translate(chair, 1 + thickness, -(1 + thickness), 1 + thickness);
    module_cube(chair, 0);

    module_identity(chair);
    module_scale(chair, thickness, h/2.0 - thickness, thickness);
    module_translate(chair, -(1 + thickness), -(1 + thickness), 1 + thickness);
    module_cube(chair, 0);

    module_identity(chair);
    module_scale(chair, thickness, h/2.0 - thickness, thickness);
    module_translate(chair, 1 + thickness, -(1 + thickness), -(1 + thickness));
    module_cube(chair, 0);

    module_identity(chair);
    module_scale(chair, thickness, h/2.0 - thickness, thickness);
    module_translate(chair, -(1 + thickness), -(1 + thickness), -(1 + thickness));
    module_cube(chair, 0);

    // back
    module_identity(chair);
    module_scale(chair, w, h / 2.0, thickness);
    module_translate(chair, 0, 1 + thickness, -1 - thickness);
    module_cube(chair, 0);

    module_module(md, chair);
}

static void table(Module *md)
{
    float h = 1;
    float w = 6;
    float l = 10;
    Module *table = module_create();
    Color tableColor = {138.0/255.0, 84.0/255.0, 59.0/255.0};
    module_color(table, tableColor);
    module_scale(table, w, h, l);
    module_cube(table, 0);

    // leg 1
    module_identity(table);
    module_scale(table, 1, w, 1);
    module_translate(table, 0.5 - w/2.0, -h/2.0 + -w/2.0, 0.5 - l/2.0);
    module_cube(table, 0);

    // leg 2
    module_identity(table);
    module_scale(table, 1, w, 1);
    module_translate(table, 0.5 - w/2.0, -h/2.0 + -w/2.0, -0.5 + l/2.0);
    module_cube(table, 0);

    // leg 3
    module_identity(table);
    module_scale(table, 1, w, 1);
    module_translate(table, -0.5 + w/2.0, -h/2.0 + -w/2.0, 0.5 - l/2.0);
    module_cube(table, 0);

    // leg 4
    module_identity(table);
    module_scale(table, 1, w, 1);
    module_translate(table, -0.5 + w/2.0, -h/2.0 + -w/2.0, -0.5 + l/2.0);
    module_cube(table, 0);
    
    module_module(md, table);
}

static void diningSet(Module *md)
{
    Module *diningSet = module_create();
    module_translate(diningSet, 0, 3.5, 0);
    table(diningSet);

    // left chair
    module_identity(diningSet);
    module_rotateY(diningSet, cos(M_PI / 2.0), sin(M_PI / 2.0));
    module_translate(diningSet, -5, 0, 0);
    chair(diningSet);

    // right chair
    module_identity(diningSet);
    module_rotateY(diningSet, -cos(M_PI / 2.0), -sin(M_PI / 2.0));
    module_translate(diningSet, 5, 0, 0);
    chair(diningSet);

    // front chair
    module_identity(diningSet);
    module_rotateY(diningSet, cos(M_PI), sin(M_PI));
    module_translate(diningSet, 0, 0, 9);
    chair(diningSet);

    // back chair
    module_identity(diningSet);
    module_translate(diningSet, 0, 0, -9);
    chair(diningSet);

    module_module(md, diningSet);
}

int main(int argc, char *argv[])
{
    int rows = 360;
    int cols = 640;
    Matrix vtm, gtm;
    View3D view;
    point_set3D( &(view.vrp), -40, 110, 20);
    vector_set( &(view.vpn), 60, -110, -20);
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

    Module *scene = module_create();
    diningSet(scene);
    module_identity(scene);
    module_translate(scene, 20, 0, 10);
    diningSet(scene);
    module_identity(scene);
    module_translate(scene, 5, 0, 30);
    diningSet(scene);
    module_identity(scene);
    module_translate(scene, 5, 0, -30);
    diningSet(scene);
    module_identity(scene);
    module_translate(scene, 25, 0, -20);
    diningSet(scene);
    module_identity(scene);
    module_translate(scene, 40, 0, 10);
    diningSet(scene);

    DrawState *ds = drawstate_create();
    ds->shade = ShadeFrame;

    Image *src = image_create(rows, cols);
    module_draw(scene, &vtm, &gtm, ds, NULL, src);
    
    image_write(src, "output/lab6/restaurant.ppm");
    module_delete(scene);
    image_free(src);

    return 0;
}
