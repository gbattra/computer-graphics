/**
 * Greg Attra
 * 11/11/2021
 * 
 * Header defining Sphere struct and API
 */

#ifndef SPHERE
#define SPHERE

#include "pyramid.h"
#include "cone.h"
#include "point.h"

typedef struct
{
    float radius;
    Point cp;
    Cone *cone;
} Hemisphere;

typedef struct
{
    float radius;
    Point cp;
    Hemisphere *top;
    Hemisphere *bot;
} Sphere;

/**
 * Create a hemisphere given the center point and radius.
 * 
 * @param cp the center point of the hemisphere
 * @param radius the radius of the hemisphere
 * 
 * @return void
 */
Hemisphere *hemisphere_createp(Point *cp, float radius);


/**
 * Create a hemisphere given the center point and radius.
 * 
 * @param cp the center point of the hemisphere
 * @param radius the radius of the hemisphere
 * 
 * @return void
 */
Sphere *sphere_createp(Point *cp, float radius);

/**
 * Divie the hemisphere n_divs times.
 * 
 * @param hsphere the hemisphere to divide
 * @param n_divs the number of divisions to make
 * @param results the resulting triangles
 * 
 * @return void
 */
void hemisphere_divide(Hemisphere *hsphere, int n_divs, LinkedList *results);


#endif
