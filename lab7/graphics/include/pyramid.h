/**
 * Greg Attra
 * 11/10/2021
 * 
 * Header file defining Pyramid struct and API.
 */

#ifndef PYRAMID
#define PYRAMID

#include "polygon.h"
#include "point.h"

typedef struct
{
    float h;
    float w;
    float l;
    int zBuffer;
    Triangle faces[4];
    Polygon *base;
    Point cp;
} Pyramid;

/**
 * Create a pyramid instance.
 * 
 * @param cp the center point of the pyramid
 * @param h the height of the pyramid
 * @param w the width of the pyramid
 * @param l the length of the pyramid
 * 
 * @return void
 */
Pyramid *pyramid_create(Point *cp, float h, float w, float l);

/**
 * Free the pyramid.
 * 
 * @param pmd the pyramid to free
 * 
 * @return void
 */
void pyramid_free(Pyramid *pmd);


#endif
