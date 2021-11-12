/**
 * Greg Attra
 * 11/11/2021
 * 
 * Implementation of the Sphere.h APi
 */

#include "sphere.h"
#include "matrix.h"
#include "cone.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Hemisphere *hemisphere_createp(Point *cp, float radius)
{
    Hemisphere *hsphere = (Hemisphere *) malloc(sizeof(Hemisphere));
    hsphere->radius = radius;
    point_copy(&hsphere->cp, cp);
    float d = sqrtf(radius*radius);
    hsphere->cone = cone_create(cp, radius, radius);

    return hsphere;
}

Sphere *sphere_createp(Point *cp, float radius)
{
    Sphere *sphere = (Sphere *) malloc(sizeof(Sphere));
    sphere->radius = radius;
    point_copy(&sphere->cp, cp);
    sphere->top = cone_create(cp, radius, radius);
    sphere->bot = cone_create(cp, radius, -radius);

    return sphere;
}
