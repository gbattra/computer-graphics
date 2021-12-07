/**
 * Greg Attra
 * 10/08/2021
 * 
 * Wrapper header around all subheaders for the grpahics engine.
 */

#ifndef GRAPHICS
#define GRAPHICS

#include "image.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "elipse.h"
#include "polyline.h"
#include "stack.h"
#include "list.h"
#include "floodfill.h"
#include "noise.h"
#include "fractals.h"
#include "vector.h"
#include "polygon.h"
#include "cube.h"
#include "matrix.h"
#include "view.h"
#include "curve.h"
#include "pyramid.h"
#include "cone.h"
#include "sphere.h"
#include "drawstate.h"
#include "lighting.h"
#include "module.h"
int readPLY(char filename[], int *nPolygons, Polygon **plist, Color **clist, int estNormals);
#endif
