/**
 * Greg Attra
 * 10/01/2021
 * 
 * Implementation of the flood fill API defined in floodfill.h
 */

#include "floodfill.h"
#include "stack.h"

void flood(Image *src, Point start, Color col)
{
    Stack *stack;
    stack = stack_create(src->rows * src->cols, sizeof(Point));
    stack_push(stack, &start);
}
