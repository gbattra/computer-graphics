/**
 * Greg Attra
 * 11/10/2021
 * 
 * Implemenatin of the Pyramid API.
 */

#include "pyramid.h"

Pyramid *pyramid_create(Point *cp, float h, float w, float l)
{
    Pyramid *pmd = (Pyramid *) malloc(sizeof(Pyramid));
    pmd->h = h;
    pmd->w = w;
    pmd->l = l;
    pmd->zBuffer = 1;
    point_copy(&pmd->cp, cp);

    float dx = (w / 2.0);
    float dz = (l / 2.0);

    Point top;
    point_set3D(&top, cp->val[0], cp->val[1] + h, cp->val[2]);

    Point base[4];
    point_set3D(&base[0], cp->val[0] + dx, cp->val[1], cp->val[2] + dz);
    point_set3D(&base[1], cp->val[0] + dx, cp->val[1], cp->val[2] - dz);
    point_set3D(&base[2], cp->val[0] - dx, cp->val[1], cp->val[2] - dz);
    point_set3D(&base[3], cp->val[0] - dx, cp->val[1], cp->val[2] + dz);
    pmd->base = polygon_createp(4, base);

    for (int f = 0; f < 4; f++)
    {
        int next_f = f + 1;
        if (next_f == 4) next_f = 0;
        
        Point vlist[3];
        point_copy(&vlist[0], &top);
        point_copy(&vlist[1], &base[f]);
        point_copy(&vlist[2], &base[next_f]);

        Triangle *face = triangle_createp(vlist);
        polygon_copy(&pmd->faces[f], face);
        polygon_free(face);
    }

    return pmd;
}

void pyramid_free(Pyramid *pmd)
{
    polygon_free(pmd->base);
    free(pmd);
}
