/**
 * Greg Attra
 * 10/06/2021
 * 
 * Implementation of the polygon API defined in polygon.h
 */

#include "polygon.h"
#include "line.h"
#include <stdlib.h>

Polygon *polygon_create(void)
{
    Polygon *pgon = (Polygon *) malloc(sizeof(Polygon));
    pgon->nVertex = 0;
    pgon->vlist = NULL;
    return pgon;
}

Polygon *polygon_createp(int nVertex, Point *vlist)
{
    Polygon *pgon = (Polygon *) malloc(sizeof(Polygon));
    pgon->nVertex = nVertex;
    pgon->zBuffer = 1;
    pgon->vlist = (Point *) malloc(sizeof(Point) * nVertex);
    for (int i = 0; i < nVertex; i++)
    {
        point_copy(&pgon->vlist[i], &vlist[i]);
    }
    return pgon;
}

void polygon_free(Polygon *pgon)
{
    free(pgon->vlist);
    free(pgon->clist);
    free(pgon->nlist);
    free(pgon);
}

void polygon_init(Polygon *pgon)
{
    pgon->nVertex = 0;
    pgon->zBuffer = 1;
    pgon->vlist = NULL;
    pgon->clist = NULL;
    pgon->nlist = NULL;
}

void polygon_set(Polygon *pgon, int numV, Point *vlist)
{
    pgon->nVertex = numV;
    free(pgon->vlist);
    pgon->vlist = (Point *) malloc(sizeof(Point) * numV);
    for (int i = 0; i < numV; i++)
    {
        point_copy(&pgon->vlist[i], &vlist[i]);
    }
}

void polygon_clear(Polygon *pgon)
{
    free(pgon->vlist);
    free(pgon->clist);
    free(pgon->vlist);
    polygon_init(pgon);
}

void polygon_setSided(Polygon *pgon, int oneSided)
{
    pgon->oneSided = oneSided;
}

void polygon_setColors(Polygon *pgon, int numV, Color *clist)
{
    pgon->nVertex = numV;
    free(pgon->clist);
    pgon->clist = (Color *) malloc(sizeof(Color) * numV);
    for (int i = 0; i < numV; i++)
    {
        color_copy(&pgon->clist[i], &clist[i]);
    }
}

// void polygon_setNormals(Polygon *pgon, int numV, Vector *nlist)
// {
//     pgon->nVertex = numV;
//     free(pgon->nlist);
//     pgon->nlist = (Vector *) malloc(sizeof(Vector) * numV);
//     for (int i = 0; i < numV; i++)
//     {
//         vector_copy(&pgon->nlist[i], &nlist[i]);
//     }
// }

void polygon_zBuffer(Polygon *pgon, int flag)
{
    pgon->zBuffer = flag;
}

void polygon_setAll(
    Polygon *pgon,
    int numV,
    Point *vlist,
    Color *clist,
    Vector *nlist,
    int zBuffer,
    int oneSided)
{
    polygon_set(pgon, numV, vlist);
    polygon_setColors(pgon, numV, clist);
    polygon_setNormals(pgon, numV, nlist);
    polygon_zBuffer(pgon, zBuffer);
    polygon_setSided(pgon, oneSided);
}

void polygon_copy(Polygon *to, Polygon *from)
{
    polygon_setAll(
        to,
        from->nVertex,
        from->vlist,
        from->clist,
        from->nlist,
        from->zBuffer,
        from->oneSided);
}

void polygon_print(Polygon *pgon, FILE *fp)
{
    fprintf(fp, "%i\n%i\n$%i\n", pgon->zBuffer, pgon->oneSided, pgon->nVertex);
    for (int i = 0; i < pgon->nVertex; i++)
    {
        point_print(&pgon->vlist[i], fp);
        color_print(&pgon->clist[i], fp);
        // vector_print(&pgon->nlist[i], fp);
    }
}

void polygon_normalize(Polygon *pgon)
{
    for (int i = 0; i < pgon->nVertex; i++)
    {
        point_normalize(&pgon->vlist[i]);
    }
}

void polygon_draw(Polygon *pgon, Image *src, Color c)
{
    for (int i = 1; i < pgon->nVertex; i++)
    {
        Point *a = &pgon->vlist[i-1];
        Point *b = &pgon->vlist[i];
        Line l;
        line_set2D(&l, a->val[0], a->val[1], b->val[0], b->val[1]);
        line_draw(&l, src, c);
    }
}

void polygon_drawFill(Polygon *pgon, Image *src, Color c);
