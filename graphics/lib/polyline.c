/**
 * Greg Attra
 * 10/04/2021
 * 
 * Implementation of the polyline API defined in polyline.h
 */

#include "polyline.h"
#include "point.h"
#include "line.h"
#include "stdlib.h"


Polyline *polyline_create(void)
{
    Polyline *pline = (Polyline *) malloc(sizeof(Polyline));
    pline->zBuffer = 1;
    pline->numVertex = 0;
    pline->vertex = NULL;
    return pline;
}

Polyline *polyline_createp(int numV, Point *vlist)
{
    Polyline *pline = (Polyline *) malloc(sizeof(Polyline));
    pline->zBuffer = 1;
    pline->numVertex = numV;
    pline->vertex = (Point *) malloc(sizeof(Point) * numV);
    for (int i = 0; i < numV; i++)
    {
        point_copy(&pline->vertex[i], &vlist[i]);
    }
    return pline;
}

void polyline_free(Polyline *pline)
{
    free(pline->vertex);
    free(pline);
}

void polyline_init(Polyline *pline)
{
    pline->zBuffer = 1;
    pline->numVertex = 0;
    pline->vertex = NULL;
}

void polyline_set(Polyline *pline, int numV, Point *vlist)
{
    pline->numVertex = numV;
    pline->vertex = (Point *) malloc(sizeof(Point) * numV);
    for (int i = 0; i < numV; i++)
    {
        point_copy(&pline->vertex[i], &vlist[i]);
    }
}

void polyline_clear(Polyline *pline)
{
    pline->numVertex = 0;
    free(pline->vertex);
    pline->vertex = NULL;
}

void polyline_zBuffer(Polyline *pline, int flag)
{
    pline->zBuffer = flag;
}

void polyline_copy(Polyline *to, Polyline *from)
{
    to->zBuffer = from->zBuffer;
    to->numVertex = from->numVertex;
    for (int i = 0; i < from->numVertex; i++)
    {
        point_copy(&to->vertex[i], &from->vertex[i]);
    }
}

void polyline_print(Polyline *pline, FILE *fp)
{
    fprintf(fp, "%i\n%i\n", pline->zBuffer, pline->numVertex);
    for (int i = 0; i < pline->numVertex; i++)
    {
        point_print(&pline->vertex[i], fp);
    }
}

void polyline_normalize(Polyline *pline)
{
    for (int i = 0; i < pline->numVertex; i++)
    {
        point_normalize(&pline->vertex[i]);
    }
}

void polyline_draw(Polyline *pline, Image *src, Color c)
{
    for (int i = 1; i < pline->numVertex; i++)
    {
        Line l;
        Point *p1 = &pline->vertex[i - 1];
        Point *p2 = &pline->vertex[i];
        line_set2D(&l, p1->val[0], p1->val[1], p2->val[0], p2->val[1]);
        line_draw(&l, src, c);
    }
}

