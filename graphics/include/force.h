/**
 * Greg Attra
 * 12/08/2021
 * 
 * Header file defining the Force struct and API.
 */

#ifndef FORCE
#define FORCE

#include "point.h"
#include "quaternion.h"
#include "vector.h"

/**
 * Defines the type of force.
 */
typedef enum
{
    ForceConstant,
    ForceHit
} ForceType;


typedef struct
{
    ForceType type;
    Vector direction;
    double power;
} Force;

/**
 * Create a default force struct.
 * 
 * @return pointer to default force struct
 */
Force *force_create(void);

/**
 * Create a foce struct with params.
 * 
 * @param type the type of the force
 * @param dir the direction of the force (unit vector)
 * @param power the power of the force
 * 
 * @return pointer to the force struct
 */
Force *force_createp(ForceType type, Vector *dir, double power);

/**
 * Free the force from mem.
 * 
 * @param force the force to free
 * 
 * @return void
 */
void force_free(Force *force);

/**
 * Apply the force given the mass, velocity and orientation of the rigidbody.
 * 
 * @param force the force to apply
 * @param mass the mass of the rb
 * @param vel the velocity of the rb
 * @param q the orientation of the rb
 * @param newVel where to write the updated velocity
 * 
 * @return void
 */
void force_apply(
    Force *force,
    double mass,
    Vector *vel,
    Quaternion *q,
    Vector *newVel);

#endif
