/**
 * Greg Attra
 * 11/21/2021
 * 
 * Header file defining Lighting API.
 */

#ifndef LIGHTING
#define LIGHTING

#include "point.h"
#include "vector.h"
#include "image.h"

#define MAX_LIGHTS 64

typedef enum
{
    LightNone,
    LightAmbient,
    LightDirect,
    LightPoint,
    LightSpot
} LightType;

typedef struct
{
    LightType type;
    Color color;
    Vector direction;
    Point position;
    float cutoff;
    float sharpness;
} Light;

typedef struct
{
    int nLights;
    Light lights[MAX_LIGHTS];
} Lighting;

/**
 * Initialize the light to default values.
 * 
 * @param light the light to initialize
 * 
 * @return void
 */
void light_init(Light *light);

/**
 * Copy from one light to anotehr.
 * 
 * @param to the target light
 * @param from the source light
 * 
 * @return void
 */
void light_copy(Light *to, Light *from);

/**
 * Allocate a lighting struct w/ default values.
 * 
 * @return a pointer to a lighting struct
 */
Lighting *lighting_create(void);

/**
 * Initialize a lighting struct to default values.
 * 
 * @param l the lighting struct to init
 * 
 * @return void
 */
void lighting_init(Lighting *l);

/**
 * Add a light to the lights list.
 * 
 * @param l the light struct to add to
 * @param type the type of light to add
 * @param color the color of the light
 * @param dir the direction of the light
 * @param pos the position of the light
 * @param cutoff the cutoff distance for the light
 * @param sharpness the sharpness of the light
 * 
 * @return void
 */
void lighting_add(
    Lighting *l,
    LightType type,
    Color *color,
    Vector *dir,
    Point *pos,
    float cutoff,
    float sharpness);

/**
 * Calculate the shading given the lighting struct and surface data.
 * 
 * @param l the lighting struct
 * @param N the surface normal
 * @param V the view vector
 * @param p the point of the normal origin
 * @param cb the body color
 * @param cs the surface color
 * @param s sharpness
 * @param oneSided whether the surface is one sided
 * @param c the resulting color to draw on the surface
 * 
 * @return void
 */
void lighting_shading(
    Lighting *l,
    Vector *N,
    Vector *V,
    Point *p,
    Color *cb,
    Color *cs,
    float s,
    int oneSided,
    Color *c);

#endif