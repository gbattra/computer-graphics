/**
 * Greg Attra
 * 11/05/2021
 * 
 * Header file defining API for Bezier curves.
 */

#ifndef CURVE
#define CURVE

#include "point.h"
#include "image.h"
#include "list.h"

typedef struct
{
    int zBuffer;
    Point vlist[4];
    
} BezierCurve;

typedef struct
{
    int zBuffer;
    Point vlist[16];
} BezierSurface;

/**
 * Set zBuffer to 1 and the curve points to the X axis between (0,1).
 * 
 * @param bc the bezier curve to initialize
 * 
 * @return void
 */
void bezierCurve_init(BezierCurve *bc);

/**
 * Set zBuffer to 1 and the curve points to the XZ plane between (0, 0) and (1,1).
 * 
 * @param bs the bezier surface to initialize
 * 
 * @return void
 */
void bezierSurface_init(BezierSurface *bs);

/**
 * Sets the control points of the curve to the points in the vlist.
 * 
 * @param bc the bezier curve to set
 * @param vlist the vertices to copy
 * 
 * @return void
 */
void bezierCurve_set(BezierCurve *bc, Point *vlist);

/**
 * Copy from one curve to another.
 * 
 * @param to the target curve
 * @param from the source curve
 * 
 * @return void
 */
void bezierCurve_copy(BezierCurve *to, BezierCurve *from);

/**
 * Sets the control poits of the surface to the points in the vlist.
 * 
 * @param bs the bezier surface to set
 * @param vlist the points the set on the surface
 * 
 * @return void
 */
void bezierSurface_set(BezierSurface *bs, Point *vlist);

/**
 * Sets the zBuffer on the curve.
 * 
 * @param bc the bezier curve to update
 * @param flag the zbuffer flag to set
 * 
 * @return void
 */
void bezierCurve_zBuffer(BezierCurve *bc, int flag);

/**
 * Sets the zBuffer on the surface.
 * 
 * @param bs the surface to update
 * @param flag the zbuffer flag to set
 * 
 * @return void
 */
void bezierSurface_zBuffer(BezierSurface *bs, int flag);

/**
 * Normalize the points in the bezier curve.
 * 
 * @param bc the bezier curve to normalize
 * 
 * @return void
 */
void bezierCurve_normalize(BezierCurve *bc);

/**
 * Divide a set of control points once using De Castlejau's algo.
 * 
 * @param points the source points to split
 * @param left the resulting left side control points
 * @param right the resulting right side control points
 * 
 * @return void
 */
void bezier_divideControlPoints(Point *points, Point *left, Point *right);

/**
 * Implementation of the decastlejau algorithm to subdivide a bezier curve.
 * 
 * @param bc the current bezier curve to subdivide
 * @param curves linked-list to store final bezier curves
 * @param divs_remaining the remaining subdivisions
 * 
 * @return void
 */
void bezierCurve_divide(
    BezierCurve *bc,
    LinkedList *curves,
    int divs_remaining);

/**
 * Draw the Bezier curve onto the image in the given color.
 * 
 * @param bc the bezier curve to draw
 * @param img the image to draw on
 * @param c the color of the curve
 * 
 * @return void
 */
void bezierCurve_draw(BezierCurve *bc, Image *src, Color c);


#endif