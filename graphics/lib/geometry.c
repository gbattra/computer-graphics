/**
 * Greg Attra
 * 10/06/2021
 * 
 * Implementation of the geometry API defined in geometry.h
 */

#include "geometry.h"


void vector_copy(Vector *to, Vector *from)
{
    to->nDims = from->nDims;
    for (int i = 0; i < from->nDims; i++)
    {
        to->d[i] = from->d[i];
    }
}

void vector_print(Vector *vector, FILE *fp)
{
    fprintf(fp, "%i\n%f\n%f\n%f\n", vector->nDims, vector->d[0], vector->d[1], vector->d[2]);
}
