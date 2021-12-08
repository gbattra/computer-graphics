/**
 * Greg Attra
 * 12/08/2021
 * 
 * Impelementation of the Force API defined in force.h
 */

#include "force.h"
#include "physics.h"
#include <stdio.h>
#include <stdlib.h>


Force *force_create(void)
{
    Force *force = (Force *) malloc(sizeof(Force));
    force->type = ForceHit;
    force->power = 0.0;
    vector_set(&force->direction, 0.0, 0.0, 0.0);

    return force;
}

Force *force_createp(ForceType type, Vector *dir, double power)
{
    Force *force = (Force *) malloc(sizeof(Force));
    force->type = type;
    force->power = power;
    vector_copy(&force->direction, dir);

    return force;
}

void force_free(Force *force)
{
    if (force != NULL) free(force);
}

void force_apply(
    Force *force,
    double mass,
    Vector *vel,
    Quaternion *q,
    Vector *newVel)
{
    double acc = force->power / mass;

    Vector fVel;
    vector_normalize(&force->direction);
    vector_set(
        &fVel,
        force->direction.val[0] * acc * DELTA_TIME,
        force->direction.val[1] * acc * DELTA_TIME,
        force->direction.val[2] * acc * DELTA_TIME);
    
    vector_set(
        &new_vel,
        vel->val[0] + fVel.val[0],
        vel->val[1] + fVel.val[1],
        vel->val[2] + fVel.val[2]);
}
