/**
 * Greg Attra
 * 12/08/2021
 * 
 * Implementation of the quaternion.h definitions.
 */

#include "quaternion.h"


void quaternion_set(Quaternion *q, double x, double y, double z, double w)
{
    q->x = x;
    q->y = y;
    q->z = z;
    q->w = w;
}

void quaternion_copy(Quaternion *to, Quaternion *from)
{
    quaternion_set(&to, from->x, from->y, from->z, from->w);
}