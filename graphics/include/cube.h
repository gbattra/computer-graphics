/**
 * Greg Attra
 * 10/20/2021
 * 
 * Header file defining the Cube API.
 */

#ifndef CUBE
#define CUBE

#include "point.h"
#include "polygon.h"
#include "image.h"

typedef struct
{
    double h;
    double w;
    double l;
    Point c;
    Polygon *sides;
} Cube;

/**
 * Create a cube. Sets up the corner points given the center and dimensions.
 * 
 * @param h the height of the cube
 * @param w the width of the cube
 * @param l the length of the cube
 * @param c the center point of the cube
 * 
 * @return void
 */
Cube *cube_create(double h, double w, double l, Point c);

/**
 * Given a preconfigured cube, setup the polygon sides.
 * 
 * @param cube the cube to setup
 * 
 * @return void
 */
void cube_setSides(Cube *cube);

/**
 * Frees the data structures within the cube.
 * 
 * @param cube the cube to free
 * 
 * @return void
 */
void cube_free(Cube *cube);

/**
 * Prints the cube to the file pointer.
 * 
 * @param cube the cube to print
 * @param fp the file pointer to print to
 * 
 * @return void
 */
void cube_print(Cube *cube, FILE *fp);

/**
 * Draw an outline of the cube.
 * 
 * @param cube the cube to draw
 * @param img the image to draw on
 * @param c the colors of the cube
 * 
 * @return void
 */
void cube_draw(Cube *cube, Image *src, Color c[6]);

/**
 * Draw and fill a cube.
 * 
 * @param cube the cube to draw
 * @param img the image to draw on
 * @param c the colors of the cube faces
 * 
 * @return void
 */
void cube_drawFill(Cube *cub, Image *src, Color c[6]);

#endif
