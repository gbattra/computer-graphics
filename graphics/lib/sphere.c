/**
 * Greg Attra
 * 11/11/2021
 * 
 * Implementation of the Sphere.h APi
 */

#include "sphere.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Hemisphere *hemisphere_createp(Point *cp, float radius)
{
    Hemisphere *hsphere = (Hemisphere *) malloc(sizeof(Hemisphere));
    point_copy(&hsphere->cp, cp);
    float d = sqrtf(2*(radius*radius));
    hsphere->top = pyramid_create(cp, radius, d, d);
    hsphere->bot = pyramid_create(cp, -radius, d, d);

    return hsphere;
}
