/**
 * Greg Attra
 * 10/12/2021
 *
 * Header file defining the Vector struct and API.
 */
 

#include "point.h"
#include <stdio.h>

typedef Point Vector;

/**
 * Set the x,y,z values on the vector.
 * 
 * @param v the vector to set
 * @param x the x value to set
 * @param y the y value to set
 * @param z the z value to set
 * 
 * @return void
 */
void vector_set(Vector *v, double x, double y, double z);

/**
 * Print the vector to a filepointer.
 * 
 * @param v the vector to print
 * @param fp the filepointer to print to
 * 
 * @return void
 */
void vector_print(Vector *v, FILE *fp);

/**
 * Copy one vector to another.
 * 
 * @param to the target vector
 * @param from the source vector
 * 
 * @return void
 */
void vector_copy(Vector *to, Vector *from);

/**
 * Return the Euclidean distance of the vector.
 * 
 * @param v the vector to measure
 * 
 * @return the length of the vector
 */
double vector_length(Vector *v);

/**
 * Normalize the vector to unit length (does not modify
 * the homogenous coord).
 * 
 * @param v the vector to normalize
 * 
 * @return void
 */
void vector_normalize(Vector *v);

/**
 * Computes the dot product of the two vectors.
 * 
 * @param a the first vector
 * @param b the second vector
 * 
 * @return the dot product of the two vectors
 */
double vector_dot(Vector *a, Vector *b);

/**
 * Computes the cross product of vectors (a,b) and puts
 * the result in vector c.
 * 
 * @param a the first vector
 * @param b the second vector
 * @param c the resulting vector
 * 
 * @return void
 */
void vector_cross(Vector *a, Vector *b, Vector *c);
