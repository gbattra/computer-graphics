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

/**
 * Draw the circle with a gradient outline between two colors.
 * 
 * @param cl the circle to draw
 * @param src the image to draw on
 * @param ca the start color of the circle
 * @param cb the end color of the circle
 * @param vert vertical gradient flag
 * 
 * @return void
 */
void circle_drawG(Circle *cl, Image *src, Color ca, Color cb, int vert);

/**
 * Draw and fill the circle with a gradient between two colors.
 * 
 * @param cl the circle to draw
 * @param src the image to draw on
 * @param ca the start color
 * @param cb the end color
 * @param vert vertical gradient flag
 * 
 * @return void
 */
void circle_drawFillG(Circle *cl, Image *src, Color ca, Color cb, int vert);

#endif
