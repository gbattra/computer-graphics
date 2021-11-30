/**
 * Greg Attra
 * 11/21/2021
 * 
 * Implementation of the lighting API defined in lighting.h
 */

#include "lighting.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    light->cutoff = cutoff;
    light->sharpness = sharpness;
    light->type = type;
    color_copy(&light->color, color);
    if (dir) vector_copy(&light->direction, dir);
    if (pos) point_copy(&light->position, pos);

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
    c->c[1] += light->color.c[1] * cb->c[1];
    c->c[2] += light->color.c[2] * cb->c[2];
}

/**
 * Compute the point light addition to the surface color.
 * 
 * @param light the light source
 * @param N the normal of the surface
 * @param V the view vector
 * @param p the point of the normal
 * @param cb the body color
 * @param cs the surface ref color
 * @param oneSided is the surface one sided
 * @param s the s coeff for the surface ref term
 * @param c the final surface color
 * 
 * @return void
 */
static void point_light(
    Light *light,
    Vector *N,
    Vector *V,
    Point *p,
    Color *cb,
    Color *cs,
    int oneSided,
    float s,
    Color *c)
{
    Vector L;
    vector_set(
        &L,
        light->position.val[0] - p->val[0],
        light->position.val[1] - p->val[1],
        light->position.val[2] - p->val[2]);
    vector_normalize(&L);

    float eps = 0.0001;
    Vector H;
    vector_set(
        &H,
        (L.val[0] + V->val[0] + eps) / 2.0,
        (L.val[1] + V->val[1] + eps) / 2.0,
        (L.val[2] + V->val[2] + eps) / 2.0);
    vector_normalize(&H);

    double theta = vector_dot(&L, N);
    double sigma = vector_dot(V, N);
    double beta = vector_dot(&H, N);
    double beta_prime = pow(beta, s);

    Color body;
    body.c[0] = light->color.c[0] * cb->c[0] * theta;
    body.c[1] = light->color.c[1] * cb->c[1] * theta;
    body.c[2] = light->color.c[2] * cb->c[2] * theta;

    Color surface;
    surface.c[0] = light->color.c[0] * cs->c[0] * beta_prime;
    surface.c[1] = light->color.c[1] * cs->c[1] * beta_prime;
    surface.c[2] = light->color.c[2] * cs->c[2] * beta_prime;

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
    vector_normalize(N);
    vector_normalize(V);

    Color tmp;
    color_set(&tmp, 0, 0, 0);

    for (int i = 0; i < l->nLights; i++)
    {
        Light *light = &l->lights[i];

        switch (light->type)
        {
            case LightAmbient:
                ambient_light(light, cb, &tmp);
                break;
            case LightPoint:
                point_light(light, N, V, p, cb, cs, oneSided, s, &tmp);
                break;
            default:
                break;
        }
    }

    if (tmp.c[0] < 0) tmp.c[0] = 0.0;
    if (tmp.c[1] < 0) tmp.c[1] = 0.0;
    if (tmp.c[2] < 0) tmp.c[2] = 0.0;

    if (tmp.c[0] > 1.0) tmp.c[0] = 1.0;
    if (tmp.c[1] > 1.0) tmp.c[1] = 1.0;
    if (tmp.c[2] > 1.0) tmp.c[2] = 1.0;

    color_copy(c, &tmp);
}
