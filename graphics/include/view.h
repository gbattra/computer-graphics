/**
 * Greg Attra
 * 10/13/2021
 * 
 * Header for defining the View2D and View3D structs and API.
 */

#ifndef VIEW
#define VIEW

#include "matrix.h"
#include "vector.h"

typedef struct
{
    Point vrp;
    double dx;
    Vector x;
    int screenx;
    int screeny;
} View2D;

typedef struct
{
    Point vrp;  // visual reference point
    Vector vpn;  // view plane normal
    Vector vup;  // view up vector
    double d;  // focal point
    double du;  // width of view
    double dv;  // height of view
    double f;  // front clip plane
    double b;  // back clip plane
    int screenx;  // image columns
    int screeny;  // image rows
} View3D;

/**
 * Sets the params on the view 2d struct.
 * 
 * @param view the view to set
 * @param vrp the view reference point
 * @param dx the width of the view port
 * @param x the direction of the x axis
 * @param screenx the number of cols on the image
 * @param screeny the number of rows on the image
 * 
 * @return void
 */
void view2D_set(View2D *view, Point *vrp, double dx, Vector *x, int screenx, int screeny);

/**
 * Transforms VTM by the specified View2D struct.
 * 
 * @param vtm the matrix to transform
 * @param v the view to transform the matrix with
 * 
 * @return void
 */
void matrix_setView2D(Matrix *vtm, View2D *v);

/**
 * Transform the VTM given the 3D view struct.
 * 
 * @param vtm the visual transformation matric
 * @param v the view to parameterize the transformations
 * 
 * @return void
 */
void matrix_setView3D(Matrix *vtm, View3D *v);

/**
 * Setup transformation matrix to convert world coords
 * to canonical view volume coords. Do this before clipping.
 * 
 * @param vtm the view transformation matrix
 * @param v the view frame configuration
 * 
 * @return void
 */
void matrix_wldTcvv(Matrix *vtm, View3D *v);

/**
 * Convert from canonical view volume coords to screen (pixel) coords.
 * Do this after clipping.
 * 
 * @param vtm the view transformation matrix
 * @param v the view frame configuration
 * @param p the perspective matrix
 * 
 * @return void
 */
void matrix_cvvTscr(Matrix *vtm, View3D *v, Matrix *p);

#endif
