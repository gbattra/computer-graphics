/**
 * Greg Attra
 * 10/04/2021
 * 
 * Implementation of the Stack API defined in stack.h
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack *stack_create(int capacity, int item_size)
{
    Stack *stack;
    stack = (Stack *) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->item_size = item_size;
    stack->top = -1;
    stack->items = (void *) malloc(item_size * capacity);
    return stack;
}

void stack_push(Stack *stack, void *item)
{
    stack->top++;
    void *dest = (char *) stack->items+(stack->top * stack->item_size);
    memcpy(dest, item, stack->item_size);
}

void stack_pop(Stack *stack, void *target)
{
    void *source = (char *) stack->items+(stack->top * stack->item_size);
    stack->top--;
    memcpy(target, source, stack->item_size);
}

int stack_size(Stack *stack)
{
    return stack->top + 1;
}

void stack_free(Stack *stack)
{
    free(stack->items);
    free(stack);
}
