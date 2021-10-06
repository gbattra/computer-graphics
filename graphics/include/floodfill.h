/**
 * Greg Attra
 * 10/04/2021
 * 
 * Header file defining flood file API
 */

#include "image.h"
#include "point.h"

/**
 * Flood fill the image from the starting point with a given
 * color.
 * 
 * @param src the image to fill
 * @param start the starting point for the algorithm
 * @param col the color of the fill
 *
 * @return void
 */
void floodfill(Image *src, Point start, Color col);
