/**
 * Greg Attra
 * 10/06/2021
 * 
 * Implementation of the polygon API defined in polygon.h
 */

#include "polygon.h"
#include "line.h"
#include "list.h"
#include <stdlib.h>

Polygon *polygon_create(void)
{
    Polygon *pgon = (Polygon *) malloc(sizeof(Polygon));
    pgon->nVertex = 0;
    pgon->zBuffer = 1;
    pgon->vlist = NULL;
    pgon->nlist = NULL;
    pgon->clist = NULL;
    return pgon;
}

Triangle *triangle_create(void)
{
    Triangle *trgl = (Triangle *) malloc(sizeof(Triangle));
    trgl->nVertex = 3;
    trgl->zBuffer = 1;
    trgl->vlist = (Point *) malloc(sizeof(Point) * 3);
    trgl->nlist = (Vector *) malloc(sizeof(Vector) * 3);
    trgl->clist = (Color *) malloc(sizeof(Color) * 3);
    return trgl;
}

Triangle *triangle_createp(Point *vlist)
{
    Triangle *trgl = (Triangle *) polygon_createp(3, vlist);
    return trgl;
}

Polygon *polygon_createp(int nVertex, Point *vlist)
{
    Polygon *pgon = (Polygon *) malloc(sizeof(Polygon));
    pgon->nVertex = nVertex;
    pgon->zBuffer = 1;
    pgon->vlist = (Point *) malloc(sizeof(Point) * nVertex);
    pgon->nlist = (Vector *) malloc(sizeof(Vector) * nVertex);
    pgon->clist = (Color *) malloc(sizeof(Color) * nVertex);

    Vector normal;
    polygon_normal(vlist, &normal);
    for (int i = 0; i < nVertex; i++)
    {
        point_copy(&pgon->vlist[i], &vlist[i]);
        vector_copy(&pgon->nlist[i], &normal);
    }

    return pgon;
}

void polygon_free(Polygon *pgon)
{
    polygon_clear(pgon);
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
    polygon_clear(pgon);

    pgon->nVertex = numV;
    pgon->vlist = (Point *) malloc(sizeof(Point) * numV);
    pgon->nlist = (Vector *) malloc(sizeof(Vector) * numV);
    pgon->clist = (Color *) malloc(sizeof(Color) * numV);

    Vector normal;
    polygon_normal(vlist, &normal);
    for (int i = 0; i < numV; i++)
    {
        point_copy(&pgon->vlist[i], &vlist[i]);
        vector_copy(&pgon->nlist[i], &normal);
    }
}

void polygon_toLines(Polygon *pgon, Line *lines)
{
    for (int l = 0; l < pgon->nVertex - 1; l++)
    {
        Line line;
        point_copy(
            &line.a,
            &pgon->vlist[l]);
        point_copy(
            &line.b,
            &pgon->vlist[l+1]);
        line_copy(&lines[l], &line);
    }

    Line line;
    point_copy(
        &line.a,
        &pgon->vlist[pgon->nVertex - 1]);
    point_copy(
        &line.b,
        &pgon->vlist[0]);
    line_copy(&lines[pgon->nVertex-1], &line);
}

void polygon_clear(Polygon *pgon)
{
    pgon->nVertex = 0;
    if (pgon->vlist) free(pgon->vlist);
    if (pgon->nlist) free(pgon->nlist);
    if (pgon->clist) free(pgon->clist);
    polygon_init(pgon);
}

void polygon_setSided(Polygon *pgon, int oneSided)
{
    pgon->oneSided = oneSided;
}

void polygon_setColors(Polygon *pgon, int numV, Color *clist)
{
    pgon->nVertex = numV;
    if (pgon->clist) free(pgon->clist);
    pgon->clist = (Color *) malloc(sizeof(Color) * numV);
    for (int i = 0; i < numV; i++)
    {
        color_copy(&pgon->clist[i], &clist[i]);
    }
}

void polygon_normal(Point *vlist, Vector *normal)
{
    Vector v21;
    v21.val[0] = vlist[1].val[0] - vlist[0].val[0];
    v21.val[1] = vlist[1].val[1] - vlist[0].val[1];
    v21.val[2] = vlist[1].val[2] - vlist[0].val[2];

    Vector v31;
    v21.val[0] = vlist[2].val[0] - vlist[0].val[0];
    v21.val[1] = vlist[2].val[1] - vlist[0].val[1];
    v21.val[2] = vlist[2].val[2] - vlist[0].val[2];

    vector_cross(&v21, &v31, normal);
}

void polygon_setNormals(Polygon *pgon, int numV, Vector *nlist)
{
    pgon->nVertex = numV;
    if (pgon->nlist) free(pgon->nlist);
    pgon->nlist = (Vector *) malloc(sizeof(Vector) * numV);
    for (int i = 0; i < numV; i++)
    {
        vector_copy(&pgon->nlist[i], &nlist[i]);
    }
}

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
    fprintf(fp, "Polygon:\n N-Vertices: %i\n", pgon->nVertex);
    for (int i = 0; i < pgon->nVertex; i++)
    {
        point_print(&pgon->vlist[i], fp);
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

    Point *a = &pgon->vlist[pgon->nVertex-1];
    Point *b = &pgon->vlist[0];
    Line l;
    line_set2D(&l, a->val[0], a->val[1], b->val[0], b->val[1]);
    line_draw(&l, src, c);
}

Point *polygon_minX(Polygon *pgon)
{
    Point *minX = &pgon->vlist[0];
    for (int v = 1; v < pgon->nVertex; v++)
    {
        if (pgon->vlist[v].val[0] < minX->val[0]) minX = &pgon->vlist[v];
    }

    return minX;
}

Point *polygon_maxX(Polygon *pgon)
{
    Point *maxX = &pgon->vlist[0];
    for (int v = 1; v < pgon->nVertex; v++)
    {
        if (pgon->vlist[v].val[0] > maxX->val[0]) maxX = &pgon->vlist[v];
    }

    return maxX;
}

void polygon_divide(Polygon *pgon, int n_divs)
{
    Polygon *tmpgon = polygon_createp(pgon->nVertex, pgon->vlist);
    int nVertex = tmpgon->nVertex * 2;
    while (n_divs > 0)
    {
        Point pnts[nVertex];
        for (int i = 0; i < tmpgon->nVertex; i++)
        {
            point_copy(&pnts[i*2], &tmpgon->vlist[i]);

            int next_i = i+1;
            if (next_i == tmpgon->nVertex) next_i = 0;

            Point *start = &tmpgon->vlist[i];
            Point *end = &tmpgon->vlist[next_i];
            Point mid;
            point_set3D(
                &mid,
                (start->val[0] + end->val[0]) / 2.0,
                (start->val[1] + end->val[1]) / 2.0,
                (start->val[2] + end->val[2]) / 2.0);
            point_copy(&pnts[(i*2) + 1], &mid);
        }
        polygon_clear(tmpgon);
        polygon_set(tmpgon, nVertex, pnts);
        nVertex *= 2;
        n_divs -= 1;
    }
    polygon_clear(pgon);
    polygon_set(pgon, tmpgon->nVertex, tmpgon->vlist);
    polygon_free(tmpgon);
}

int triangle_compare(const void *one, const void *two)
{
    return 0;
}

void triangle_divide(Triangle *trgl, Triangle trgls[4])
{
    Point pnts[12];
    for (int i = 0; i < 3; i++)
    {
        point_copy(&pnts[i*2], &trgl->vlist[i]);

        int next_i = i+1;
        if (next_i == 3) next_i = 0;

        Point *start = &trgl->vlist[i];
        Point *end = &trgl->vlist[next_i];
        Point mid;
        point_set3D(
            &mid,
            (start->val[0] + end->val[0]) / 2.0,
            (start->val[1] + end->val[1]) / 2.0,
            (start->val[2] + end->val[2]) / 2.0);
        point_copy(&pnts[(i*2) + 1], &mid);
    }

    Triangle *tmp = triangle_create();
    for (int i = 0; i < 5; i += 2)
    {
        int c1 = i;
        int c2 = i + 1;
        int c3 = i - 1;
        if (c3 < 0) c3 = 5;

        point_copy(&tmp->vlist[0], &pnts[c1]);
        point_copy(&tmp->vlist[1], &pnts[c2]);
        point_copy(&tmp->vlist[2], &pnts[c3]);
        polygon_copy(&trgls[i/2], tmp);
    }

    point_copy(&tmp->vlist[0], &pnts[1]);
    point_copy(&tmp->vlist[1], &pnts[3]);
    point_copy(&tmp->vlist[2], &pnts[5]);
    polygon_copy(&trgls[3], tmp);

    polygon_free(tmp);
}

void polygon_shade(Polygon *pgon, DrawState *ds, Lighting *light)
{
    if (ds->shade == ShadeFrame) return;
    if (ds->shade == ShadeConstant)
    {
        for (int i = 0; i < pgon->nVertex; i++)
        {
            color_copy(&pgon->clist[i], &ds->color);
        }
        return;
    }
    if (ds->shade == ShadeFlat)
    {
        Color c;
        Vector V;
        V.val[0] = ds->viewer.val[0] - pgon->vlist[0].val[0];
        V.val[1] = ds->viewer.val[1] - pgon->vlist[0].val[1];
        V.val[2] = ds->viewer.val[2] - pgon->vlist[0].val[2];
        lighting_shading(
            light,
            &pgon->nlist[0],
            &V,
            &pgon->vlist[0],
            &ds->body,
            &ds->surface,
            ds->surfaceCoeff,
            pgon->oneSided,
            &c);

        for (int i = 0; i < pgon->nVertex; i++)
        {
            color_copy(&pgon->clist[i], &c);
        }
        return;
    }
    if (ds->shade == ShadeGouraud)
    {
        for (int i = 0; i < pgon->nVertex; i++)
        {
            Vector V;
            V.val[0] = ds->viewer.val[0] - pgon->vlist[i].val[0];
            V.val[1] = ds->viewer.val[1] - pgon->vlist[i].val[1];
            V.val[2] = ds->viewer.val[2] - pgon->vlist[i].val[2];
            lighting_shading(
                light,
                &pgon->nlist[i],
                &V,
                &pgon->vlist[i],
                &ds->body,
                &ds->surface,
                ds->surfaceCoeff,
                pgon->oneSided,
                &pgon->clist[i]);
        }
        return;
    }
}

void polygon_drawShade(Polygon *pgon, Image *src, DrawState *ds, Lighting *light)
{
    if (ds->shade == ShadeFrame)
    {
        polygon_draw(pgon, src, ds->color);
        return;
    }

    polygon_drawFill(pgon, src, ds);
}
