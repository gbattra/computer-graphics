/**
 * Greg Attra
 * 10/01/2021
 * 
 * Defines the Elipse object and API.
 */

#include "point.h"

typedef struct
{
    double ra;
    double rb;
    double a;
    Point c;
} Elipse;

/**
 * Sets the provided attribute values on the elipse.
 * 
 * @param el the elipse to update
 * @param ra the major axis radius
 * @param rb the minor axis radius
 * @param a the angle of the elipse relative to x axis
 * 
 * @return void
 */
void elipse_set(Elipse *el, Point c, double ra, double rb, double a);

/**
 * Draws the elipse on the image.
 * 
 * @param el the elipse to draw
 * @param src the image to draw on
 * @param c the color of the elipse
 * 
 * @return void
 */
void elipse_draw(Elipse *el, Image *src, Color c);

/**
 * Draw and fill an elipse.
 * 
 * @param el the elipse to draw
 * @param src the image to draw on
 * @param c the color of the elipse
 * 
 * @return void
 */
void elipse_drawFill(Elipse *el, Image *src, Color c);

