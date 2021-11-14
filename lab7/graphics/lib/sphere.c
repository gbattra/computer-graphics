/**
 * Greg Attra
 * 11/11/2021
 * 
 * Implementation of the Sphere.h APi
 */

#include "sphere.h"
#include "matrix.h"
#include "cone.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Hemisphere *hemisphere_createp(Point *cp, float radius)
{
    Hemisphere *hsphere = (Hemisphere *) malloc(sizeof(Hemisphere));
    hsphere->radius = radius;
    point_copy(&hsphere->cp, cp);
    float d = sqrtf(radius*radius);
    hsphere->cone = cone_create(cp, radius, radius);

    return hsphere;
}

Sphere *sphere_createp(Point *cp, float radius)
{
    Sphere *sphere = (Sphere *) malloc(sizeof(Sphere));
    sphere->radius = radius;
    point_copy(&sphere->cp, cp);
    
    Hemisphere *top = (Hemisphere *) malloc(sizeof(Hemisphere));
    top->radius = radius;
    point_copy(&top->cp, cp);
    top->cone = cone_create(cp, radius, radius);
    sphere->top = top;
    
    Hemisphere *bot = (Hemisphere *) malloc(sizeof(Hemisphere));
    bot->radius = radius;
    point_copy(&bot->cp, cp);
    bot->cone = cone_create(cp, radius, -radius);
    sphere->bot = bot;

    return sphere;
}


typedef struct
{
    Triangle *triangle;
    int n_divs;
} LinkedListItem;

static int itemCompare(const void *one, const void *two)
{
    return 1;
}

void hemisphere_divide(Hemisphere *hsphere, int n_divs, LinkedList *results)
{
    LinkedList *queue = ll_new();
    for (int i = 0; i < 3; i++)
    {
        LinkedListItem *item = (LinkedListItem *) malloc(sizeof(LinkedListItem));
        item->triangle = &hsphere->cone->faces[i];
        item->n_divs = n_divs;
        ll_insert(queue, item, &itemCompare);
    }

    LinkedListItem *curr = ll_pop(queue);
    while (curr)
    {
        if (curr->n_divs == 0)
        {
            ll_insert(results, curr->triangle, &triangle_compare);
            free(curr);
            curr = ll_pop(queue);
            continue;
        }

        Triangle *triangles = (Triangle *) malloc(sizeof(Triangle) * 4);
        triangle_divide(curr->triangle, triangles);

        for (int i = 0; i < 4; i++)
        {
            point_project(&triangles[i].vlist[0], &hsphere->cp, hsphere->radius, &triangles[i].vlist[0]);
            point_project(&triangles[i].vlist[1], &hsphere->cp, hsphere->radius, &triangles[i].vlist[1]);
            point_project(&triangles[i].vlist[2], &hsphere->cp, hsphere->radius, &triangles[i].vlist[2]);

            LinkedListItem *item = (LinkedListItem *) malloc(sizeof(LinkedListItem));
            item->triangle = &triangles[i];
            item->n_divs = curr->n_divs - 1;
            ll_insert(queue, item, &itemCompare);
        }

        free(curr);
        curr = ll_pop(queue);
    }
}
