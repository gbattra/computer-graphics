/**
 * Greg Attra
 * 11/21/2021
 * 
 * Implementation of the lighting API defined in lighting.h
 */

#include "lighting.h"
#include <stdio.h>
#include <stdlib.h>

void light_init(Light *light)
{
    light->cutoff = 0;
    light->sharpness = 1;
    light->type = LightNone;
    color_set(&light->color, 0, 0, 0);
    vector_set(&light->direction, 0, 0, 0);
    point_set3D(&light->position, 0, 0, 0);
}

void light_copy(Light *to, Light *from)
{
    to->cutoff = from->cutoff;
    to->sharpness = from->sharpness;
    to->type = from->type;
    color_copy(&to->color, &from->color);
    vector_copy(&to->direction, &from->direction);
    point_copy(&to->position, &from->position);
}

Lighting *lighting_create(void)
{
    Lighting *l = (Lighting *) malloc(sizeof(Lighting));
    l->nLights = 0;

    return l;
}

void lighting_init(Lighting *l)
{
    l->nLights = 0;
}

void lighting_add(
    Lighting *l,
    LightType type,
    Color *color,
    Vector *dir,
    Point *pos,
    float cutoff,
    float sharpness)
{
    Light *light = &l->lights[l->nLights];
    light->cutoff = 0;
    light->sharpness = 1;
    light->type = LightNone;
    color_set(&light->color, 0, 0, 0);
    vector_set(&light->direction, 0, 0, 0);
    point_set3D(&light->position, 0, 0, 0);

    l->nLights += 1;
}

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
