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

#endif
