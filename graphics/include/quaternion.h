/**
 * Greg Attra
 * 12/08/2021
 * 
 * Header file defining the Quaternion struct and API.
 */

#ifndef QUATERNION
#define QUATERNION

typedef struct
{
    double x, y, z, w;
} Quaternion;

/**
 * Set the x y z w vals of the quat.
 * 
 * @param x the x val
 * @param y the y val
 * @param z the z val
 * @param w the w val
 * 
 * @return void
 */
void quaternion_set(double x, double y, double z, double w);

/**
 * Copy from one quat to another.
 * 
 * @param to the target quat
 * @param from the source quat
 * 
 * @return void
 */
void quaternion_copy(Quaternion *to, Quaternion *from);

#endif
