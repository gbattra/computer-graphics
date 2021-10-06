/**
 * Greg Attra
 * 09/30/2021
 * 
 * Header file for the circle API.
 */

#ifndef CIRCLE
#define CIRCLE

#include "point.h"
#include "image.h"

typedef struct
{
    double radius;
    Point center;
} Circle;

/**
 * Set the radius and center of the circle.
 * 
 * @param c the circle to set
 * @param tc the center of the circle
 * @param tr the radius of the circle
 * 
 * @return void
 */
void circle_set(Circle *c, Point tc, double tr);

/**
 * Draw an outline of a circle on the image.
 * 
 * @param c the circle to draw
 * @param src the image to draw on
 * @param c the color of the circle
 *
 * @return void
 */
void circle_draw(Circle *circle, Image *src, Color c);

/**
 * Draw and fill a circle on the image.
 * 
 * @param c the circle to draw
 * @param src the image to draw on
 * @param c the color of the circle
 *
 * @return void
 */
void circle_drawFill(Circle *circle, Image *src, Color c);


#endif
