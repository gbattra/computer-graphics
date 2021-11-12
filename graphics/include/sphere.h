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
    Cone *top;
    Cone *bot;
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

#endif
