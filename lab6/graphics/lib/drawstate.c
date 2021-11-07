/**
 * Greg Attra
 * 10/23/2021
 * 
 * Implementation of the draw state API defined in drawstate.h
 */

#include "drawstate.h"
#include <stdlib.h>


DrawState *drawstate_create(void)
{
    Point p = {0.0, 0.0, 0.0};
    Color c = {1.0, 1.0, 1.0};
    DrawState *ds = (DrawState *) malloc(sizeof(DrawState));
    color_copy(&ds->color, &c);
    color_copy(&ds->flatColor, &c);
    color_copy(&ds->body, &c);
    color_copy(&ds->surface, &c);
    ds->shade = ShadeDepth;
    point_copy(&ds->viewer, &p);
    ds->zBuffer = 1;
    ds->surfaceCoeff = 0;

    return ds;
}

void drawstate_setColor(DrawState *ds, Color c)
{
    color_copy(&ds->color, &c);
}

void drawstate_setFlatColor(DrawState *ds, Color c)
{
    color_copy(&ds->flatColor, &c);
}

void drawstate_setBody(DrawState *ds, Color c)
{
    color_copy(&ds->body, &c);
}

void drawstate_setSurface(DrawState *ds, Color c)
{
    color_copy(&ds->surface, &c);
}

void drawstate_setSurfaceCoeff(DrawState *ds, float sc)
{
    ds->surfaceCoeff = sc;
}

void drawstate_setShade(DrawState *ds, ShadeMethod sm)
{
    ds->shade = sm;
}

void drawstate_copy(DrawState *to, DrawState *from)
{
    color_copy(&to->color, &from->color);
    color_copy(&to->flatColor, &from->flatColor);
    color_copy(&to->body, &from->body);
    color_copy(&to->surface, &from->surface);
    to->shade = from->shade;
    point_copy(&to->viewer, &from->viewer);
    to->zBuffer = from->zBuffer;
    to->surfaceCoeff = from->surfaceCoeff;
}

void drawstate_free(DrawState *ds)
{
    free(ds);
}
