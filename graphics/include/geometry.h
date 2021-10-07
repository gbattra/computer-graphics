/**
 * Greg Attra
 * 10/06/2021
 * 
 * Definition of structs for 3D math / geometry.
 */

#ifndef GEOMETRY
#define GEOMETRY

#include <stdio.h>

typedef struct
{
    int nDims;
    double d[3];
} Vector;

/**
 * Copy from one vector to another.
 * 
 * @param to the vector to copy to
 * @param from the vector to copy from
 * 
 * @return void
 */
void vector_copy(Vector *to, Vector *from);

/**
 * Print the vector to the filepointer.
 * 
 * @param vector the vector to print
 * @param fp the filepointer to print to
 * 
 * @return void
 */
void vector_print(Vector *vector, FILE *fp);

#endif
