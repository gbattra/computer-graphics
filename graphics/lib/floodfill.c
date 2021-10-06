/**
 * Greg Attra
 * 10/01/2021
 * 
 * Implementation of the flood fill API defined in floodfill.h
 */

#include "floodfill.h"
#include "stack.h"
#include "image.h"


void floodfill(Image *src, Point start, Color col)
{
    Stack *stack;
    stack = stack_create(src->rows * src->cols, sizeof(Point));
    stack_push(stack, &start);

    Color start_col = image_getColor(src, start.val[1], start.val[0]);

    while (stack->top >= 0)
    {
        Point current;
        stack_pop(stack, &current);
        Color curr_col = image_getColor(src, current.val[1], current.val[0]);

        if (color_compare(&curr_col, &start_col) > 0) continue;

        image_setColor(src, current.val[1], current.val[0], col);

        Point right;
        point_set2D(&right, current.val[0] + 1, current.val[1]);

        Point left;
        point_set2D(&left, current.val[0] - 1, current.val[1]);

        Point top;
        point_set2D(&top, current.val[0], current.val[1] + 1);

        Point bottom;
        point_set2D(&bottom, current.val[0], current.val[1] - 1);

        stack_push(stack, &right);
        stack_push(stack, &left);
        stack_push(stack, &top);
        stack_push(stack, &bottom);
    }
}
