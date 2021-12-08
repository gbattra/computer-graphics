/**
 * Greg Attra
 * 12/08/2021
 * 
 * Header file defining the Rigidbody struct and API.
 */

#ifndef RIGIDBODY
#define RIGIDBODY

#include "force.h"
#include "point.h"
#include "vector.h"
#include "quaternion.h"
#include "list.h"
#include "module.h"

typedef struct
{
    int useGravity;
    double mass;
    double friction;
    LinkedList *forces;
    Point position;
    Vector velocity;
    Quaternion orientation;
    Module *md;
} Rigidbody;

/**
 * Create a default rigidbody.
 * 
 * @return a default rigidobdy
 */
Rigidbody *rigidbody_create(void);

/**
 * Create a rigidbody with params.
 * 
 * @param useGravity should we apply gravity to the rb
 * @param mass the mass of the rigidbody
 * @param friction the friction coeff of the rigidbody
 * @param pos the position of the rigidbody
 * @param vel the velocity of the rigidbody
 * @param q the orientation of the rigidobdy
 * @param md the module / visual representtion of the rigidbody
 * 
 * @return pointer to the new rigidbody instance
 */
Rigidbody *rigidbody_createp(
    int useGravity,
    double mass,
    double friction,
    Point *pos,
    Vector *vel,
    Quaternion *q,
    Module *md);

/**
 * Set the mass of the rigidbody.
 * 
 * @param rb the rigidbody to update
 * @param mass the mass to set
 * 
 * @return void
 */
void rigidbody_setMass(Rigidbody *rb, double mass);

/**
 * Set the friction coeff on the rigidbody.
 * 
 * @param rb the rigidbody to udpate
 * @param friction the friction to set
 * 
 * @return void
 */
void rigidbody_setFriction(Rigidbody *rb, double friction);

/**
 * Set the position of the rigidbody.
 * 
 * @param rb the rigidbody to udpate
 * @param pos the position of the rb
 * 
 * @return void
 */
void rigidbody_setPosition(Rigidbody *rb, Point *pos);

/**
 * Set the velocity of the rigidbody.
 * 
 * @param rb the rigidbody to update
 * @param vel the velocity to set
 * 
 * @return void
 */
void rigidbody_setVelocity(Rigidbody *rb, Vector *vel);

/**
 * Set flag on using gravity.
 * 
 * @param rb the rigidbody to update
 * @param useGravity the use gravity flag
 * 
 * @return void
 */
void rigidbody_setUseGravity(Rigidbody *rb, int useGravity);

/**
 * Set the orientation of the rigidbody.
 * 
 * @param rb the rigidbody to update
 * @param q the orientation to set
 * 
 * @return void
 */
void rigidbody_setOrientation(Rigidbody *rb, Quaternion *q);

/**
 * Set the module visualization of the rigidbody.
 * 
 * @param rb the rigidbody to update
 * @param md the module to set
 * 
 * @return void
 */
void rigidbody_setModule(Rigidbody *rb, Module *md);

/**
 * Add a force to the rigidbody.
 * 
 * @param rb the rb to update
 * @param f the force to add
 * 
 * @return void
 */
void rigidbody_addForce(Rigidbody *rb, Force *f);

/**
 * Free the rb from mem.
 * 
 * @param rb the rigidbody to free
 * 
 * @return void
 */
void rigidbody_free(Rigidbody *rb);

/**
 * Apply the forces to the rigidbody for one time-step.
 * 
 * @param rb the rigidbody to tick
 * 
 * @return void
 */
void rigidbody_tick(Rigidbody *rb);

/**
 * Render the rigidbody by adding its module to the scene graph.
 * 
 * @param rb the rigidbody to render
 * @param md the scene graph to add to
 * 
 * @return void
 */
void rigidbody_render(Rigidbody *rb, Module *md);

#endif
