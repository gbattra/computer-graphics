/**
 * Greg Attra
 * 10/09/2021
 * 
 * Implementation of the barycentric fill algorithm
 * defined in polygon.h
 */

#include "polygon.h"

/**
 * Computes the implicit equation for the line.
 * 
 * @param x the x coord
 * @param y the y coord
 * @param start the start of the line
 * @param end the end of the line
 * 
 * @return the computed value
 */
static double pointline(double x, double y, Point *start, Point *end)
{
    double y0= start->val[1];
    double y1 = end->val[1];
    double x0 = start->val[0];
    double x1 = end->val[0];

    return (y0 - y1)*x + (x1 - x0)*y + x0*y1 - x1*y0;
}

/**
 * Computes the barycentric coord given the (x,y) coord and the line start and end points.
 * 
 * @param x the x coord
 * @param y the y coord
 * @param top0 the starting point of the edge of the triangle
 * @param top1 the ending point of the edge of the triangle
 * @param bot the point of the triangle tangential to the edge used
 *
 * @return the barycentric coord
 */
static double barycentric_coord(double x, double y, Point *top0, Point *top1, Point *bot)
{
    double numerator = pointline(x, y, top0, top1);
    double denominator = pointline(bot->val[0] + 0.5, bot->val[1] + 0.5, top0, top1);

    return numerator / denominator;
}

void polygon_drawFillB(Polygon *pgon, Image *src, DrawState *ds)
{
    if (pgon->nVertex != 3)
        printf("%s\n", "Invalid polygon does not have exactly 3 vertices");

    Point *p = &pgon->vlist[0];
    double minX = p->val[0];
    double minY = p->val[1];
    double maxX = p->val[0];
    double maxY = p->val[1];

    for (int v = 1; v < pgon->nVertex; v++)
    {
        p = &pgon->vlist[v];
        if (p->val[0] < minX) minX = p->val[0];
        if (p->val[0] > maxX) maxX = p->val[0];
        if (p->val[1] < minY) minY = p->val[1];
        if (p->val[1] > maxY) maxY = p->val[1];
    }

    Point *a = &pgon->vlist[0];
    Point *b = &pgon->vlist[1];
    Point *c = &pgon->vlist[2];

    Color *ac = &pgon->clist[0];
    Color *bc = &pgon->clist[1];
    Color *cc = &pgon->clist[2];

    for (int i = minY; i < maxY; i++)
    {
        for (int j = minX; j < maxX; j++)
        {   
            double x = ((double) j) + 0.5;
            double y = ((double) i) + 0.5;
            double beta = barycentric_coord(x, y, c, a, b);
            double gamma = barycentric_coord(x, y, a, b, c);
            double alpha = 1.0 - beta - gamma;
            
            if ((0 <= alpha) && (alpha <= 1) && (0 <= beta) && (beta <= 1) && (0 <= gamma) && (gamma <= 1))
            {
                double z = 1.0 / ((alpha * a->val[2]) + (beta * b->val[2]) + (gamma * c->val[2]));
                if (z < image_getz(src, i, j)) continue;

                FPixel pix;
                pix.a = 1.0;
                pix.z = z;
                if (ds->shade == ShadeDepth)
                {
                    pix.rgb[0] = (1.0 - (1.0/z)) * ds->color.c[0];
                    pix.rgb[1] = (1.0 - (1.0/z)) * ds->color.c[1];
                    pix.rgb[2] = (1.0 - (1.0/z)) * ds->color.c[2];
                } else
                {
                    pix.rgb[0] = (alpha * ac->c[0]) + (beta * bc->c[0]) + (gamma * cc->c[0]);
                    pix.rgb[1] = (alpha * ac->c[1]) + (beta * bc->c[1]) + (gamma * cc->c[1]);
                    pix.rgb[2] = (alpha * ac->c[2]) + (beta * bc->c[2]) + (gamma * cc->c[2]);
                }

                image_setf(src, i, j, pix);
            }
        }
    }
}
