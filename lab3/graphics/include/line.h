/**
 * Greg Attra
 * 09/30/2021
 * 
 * Header file for Line struct and API.
 */

#ifndef LINE
#define LINE

#include "point.h"

typedef struct
{
    int zBuffer;
    Point a;
    Point b;
} Line;

/**
 * Set the starting and end points on the line.
 * 
 * @param l the line to set
 * @param x0 the start x
 * @param y0 the start y
 * @param x1 the end x
 * @param y1 the end y
 *
 * @return void
 */
void line_set2D(Line *l, double x0, double y0, double x1, double y1);

/**
 * Initialize a line to ta and tb.
 * 
 * @param l the line to initialize
 * @param ta the start point
 * @param tb the end point
 * 
 * @return void
 */
void line_set(Line *l, Point ta, Point tb);

/**
 * Set the zBuffer flag on the line.
 * 
 * @param l the line to set
 * @param flag the zbuffer flag
 * 
 * @return void
 */
void line_zBuffer(Line *l, int flag);

/**
 * Normalize the start and endpoints by the h coord.
 *
 * @param l the line to normalize
 *
 * @return void
 */
void line_normalize(Line *l);

/**
 * Copy the contents from one line to another.
 * 
 * @param to the target line
 * @param from the source line
 * 
 * @return void
 */
void line_copy(Line *to, Line *from);

/**
 * Draw the line on the image.
 * 
 * @param l the line to drawm
 * @param src the image to draw on
 * @param c the color of the line
 * 
 * @return void
 */
void line_draw(Line *l, Image *src, Color c);

#endif
