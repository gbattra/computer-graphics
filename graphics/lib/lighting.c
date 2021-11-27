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
    if (l->nLights == MAX_LIGHTS) return;
    Light *light = &l->lights[l->nLights];
    light->cutoff = 0;
    light->sharpness = 1;
    light->type = LightNone;
    color_set(&light->color, 0, 0, 0);
    vector_set(&light->direction, 0, 0, 0);
    point_set3D(&light->position, 0, 0, 0);

    l->nLights += 1;
}

/**
 * Compute the ambient light addition to the surface color.
 * 
 * @param light the light source
 * @param bc the body color of the surface
 * @param c the final surface color
 * 
 * @return void
 */
static void ambient_light(Light *light, Color *cb, Color *c)
{
    c->c[0] += light->color.c[0] * cb->c[0];
    c->c[1] += light->color.c[1] * cb->c[0];
    c->c[2] += light->color.c[2] * cb->c[0];
}

/**
 * Compute the point light addition to the surface color.
 * 
 * @param light the light source
 * @param N the normal of the surface
 * @param V the view vector
 * @param cb the body color
 * @param cs the surface ref color
 * @param c the final surface color
 * 
 * @return void
 */
static void point_light(
    Light *light,
    Vector *N,
    Vector *V,
    Color *cb,
    Color *cs,
    Color *c)
{
    Color cbl;
    cbl.c[0] = cb->c[0] * light->color.c[0];
    cbl.c[0] = cb->c[1] * light->color.c[1];
    cbl.c[0] = cb->c[2] * light->color.c[2];

    Color csl;
    csl.c[0] = cs->c[0] * light->color.c[0];
    csl.c[0] = cs->c[1] * light->color.c[1];
    csl.c[0] = cs->c[2] * light->color.c[2];

    Vector H;
    vector_set(
        &H,
        (light->direction.val[0] + V->val[0]) / 2.0,
        (light->direction.val[1] + V->val[1]) / 2.0,
        (light->direction.val[2] + V->val[2]) / 2.0);
    double HN = vector_dot(&H, N);
    double LN = vector_dot(&light->direction, N);

    Color body;
    body.c[0] = cbl.c[0] * LN;
    body.c[1] = cbl.c[1] * LN;
    body.c[2] = cbl.c[2] * LN;

    Color surface;
    surface.c[0] = csl.c[0] * HN;
    surface.c[1] = csl.c[1] * HN;
    surface.c[2] = csl.c[2] * HN;

    c->c[0] += body.c[0] + surface.c[0];
    c->c[1] += body.c[1] + surface.c[1];
    c->c[2] += body.c[2] + surface.c[2];
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
    Color *c)
{
    for (int i = 0; i < l->nLights; i++)
    {
        Light *light = &l->lights[i];
        switch (light->type)
        {
            case LightAmbient:
                ambient_light(light, cb, c);
                break;
            case LightPoint:
                point_light(light, N, V, cb, cs, c);
                break;
            default:
                break;
        }
    }
}
