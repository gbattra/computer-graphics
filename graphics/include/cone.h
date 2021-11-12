/**
 * Greg Attra
 * 11/10/2021
 * 
 * Definition of Cone struct and API.
 */

#ifndef CONE
#define CONE

#include "polygon.h"
#include "point.h"

typedef struct
{
    float r;
    float h;
    Point cp;
    Triangle *faces;
    Polygon *base;
} Cone;

/**
 * Create a cone.
 * 
 * @param cp the center point of the cone
 * @param r the radius of the cone
 * @param h the height of the cone
 * 
 * @return void
 */
Cone *cone_create(Point *cp, float r, float h);

/**
 * Free a cone struct.
 * 
 * @param cone the cone to free
 * 
 * @return void
 */
void cone_free(Cone *cone);

/**
 * Clear a cone struct.
 * 
 * @param cone the cone to clear
 * 
 * @return void
 */
void cone_clear(Cone *cone);

/**
 * Set the faces and base on the cone.
 * 
 * @param cone the cone to update
 * @param h the height of the cone
 * @param r the radius of the cone
 * @param faces the faces to set
 * @param base the base polygon to set
 * 
 * @return void
 */
void cone_set(Cone *cone, float h, float r, Triangle *faces, Polygon *base);

/**
 * Divide the cone n_divs times.
 * 
 * @param cone the cone to divide
 * @param n_divs the number of times to divide the cone
 * 
 * @return void
 */
void cone_divide(Cone *cone, int n_divs);

#endif
