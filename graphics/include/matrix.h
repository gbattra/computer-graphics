/**
 * Greg Attra
 * 10/12/2021
 * 
 * Definition of the Matrix struct and API.
 */

#ifndef MATRIX
#define MATRIX

#include <stdio.h>
#include "vector.h"
#include "point.h"
#include "polygon.h"
#include "polyline.h"
#include "line.h"
#include "circle.h"
#include "elipse.h"

typedef struct
{
    double m[4][4];
} Matrix;

/**
 * Prints the matrix to the filepointer.
 * 
 * @param m the matrix to print
 * @param fp the filepointer to print to
 * 
 * @return void
 */
void matrix_print(Matrix *m, FILE *fp);

/**
 * Set all matrix values to zero.
 * 
 * @param m the matrix to clear
 * 
 * @return void
 */
void matrix_clear(Matrix *m);

/**
 * Set the matrix to the identity matrix.
 * 
 * @param m
 * 
 * @return void
 */
void matrix_identity(Matrix *m);

/**
 * Get the value at (i, j).
 * 
 * @param m the matrix to query
 * @param i the row of the value
 * @param j the column of the value
 * 
 * @return the value at (i,j)
 */
double matrix_get(Matrix *m, int i, int j);

/**
 * Sets the value at (i, j) to v.
 * 
 * @param m the matrix to update
 * @param i the row of the value
 * @param j the column of the value
 * @param v the value to set
 * 
 * @return void
 */
void matrix_set(Matrix *m, int i, int j, double v);

/**
 * Copy one matrix to the other.
 * 
 * @param to the target matrix
 * @param from the source matrix
 * 
 * @return void
 */
void matrix_copy(Matrix *to, Matrix *from);

/**
 * Transpose the matrix in place.
 * 
 * @param m the matrix to transpose
 * 
 * @return void
 */
void matrix_transpose(Matrix *m);

/**
 * Multiply a with b and put result in c (assumes a & b are 4x4 matrices).
 * 
 * @param a the left matrix
 * @param b the right matrix
 * @param c the resulting matrix
 * 
 * @return void
 */
void matrix_multiply(Matrix *a, Matrix *b, Matrix *c);

/**
 * Transform the point p by matrix m and put result in q.
 * 
 * @param m the transformation matrix
 * @param p the point to transform
 * @param q the resulting point
 * 
 * @return void
 */
void matrix_xformPoint(Matrix *m, Point *p, Point *q);

/**
 * Transform the vector p by matrix m and put result in q.
 * 
 * @param m the transformation matrix
 * @param p the vector to transform
 * @param q the resulting vector
 * 
 * @return void
 */
void matrix_xformVector(Matrix *m, Vector *p, Vector *q);

/**
 * Transform the points and normals in polygon p by matrix m.
 * 
 * @param m the transformation matrix
 * @param p the polygon to transform
 * 
 * @return void
 */
void matrix_xformPolygon(Matrix *m, Polygon *p);

/**
 * Transform the polyline p by the matrix m.
 * 
 * @param m the transformation matrix
 * @param p the polyline to transform
 * 
 * @return void
 */
void matrix_xformPolyline(Matrix *m, Polyline *p);

/**
 * Transform the point in line l by the matrix m.
 * 
 * @param m the transformation matrix
 * @param l the line to transform
 * 
 * @return void
 */
void matrix_xformLine(Matrix *m, Line *l);

/**
 * Transform the points and radius in the circle by matrix m.
 * 
 * @param m the transformation matrix
 * @param c the circle to transform
 * 
 * @return void
 */
void matrix_xformCircle(Matrix *m, Circle *c);

/**
 * Transform the points and radii of the elipse by matrix m.
 * 
 * @param m the transformation matrix
 * @param e the elipse to transform
 * 
 * @return void
 */
void matrix_xformElipse(Matrix *m, Elipse *e);

/**
 * Scale the matrix by sx and sy.
 * 
 * @param m the matrix to scale
 * @param sx the x scale factor
 * @param sy the y scale factor
 * 
 * @return void
 */
void matrix_scale2D(Matrix *m, double sx, double sy);

/**
 * Translate the matrix by tx and ty.
 * 
 * @param m the matrix to translate
 * @param tx the x translation
 * @param ty the y translation
 * 
 * @return void
 */
void matrix_translate2D(Matrix *m, double tx, double ty);

/**
 * Shear the matrix by sx and sy.
 * 
 * @param m the matrix to shear
 * @param sx the x shear
 * @param sy the y shear
 * 
 * @return void
 */
void matrix_shear2D(Matrix *m, double sx, double sy);

/**
 * Translate the matrix in 3D space by tx, ty and tz.
 * 
 * @param m the matrix to translate
 * @param tx the x translation
 * @param ty the y translation
 * @param tz the z translation
 * 
 * @return void
 */
void matrix_translate(Matrix *m, double tx, double ty, double tz);

/**
 * Scale the 3D matrix by sx, sy and sz.
 * 
 * @param m the matrix to scale
 * @param sx the x scale factor
 * @param sy the y scale factor
 * @param sz the z scale factor
 * 
 * @return void
 */
void matrix_scale(Matrix *m, double sx, double sy, double sz);

/**
 * Rotate the matrix about the X axis by cth and sth.
 * 
 * @param m the matrix to rotate
 * @param cth the cos(theta) angle
 * @param sth the sin(theta) angle
 * 
 * @return void
 */
void matrix_rotateX(Matrix *m, double cth, double sth);

/**
 * Rotate the matrix about the Y axis by cth and sth.
 * 
 * @param m the matrix to rotate
 * @param cth the cos(theta) angle
 * @param sth the sin(theta) angle
 * 
 * @return void
 */
void matrix_rotateY(Matrix *m, double cth, double sth);

/**
 * Rotate the matrix about the Z axis by cth and sth.
 * 
 * @param m the matrix to rotate
 * @param cth the cos(theta) angle
 * @param sth the sin(theta) angle
 * 
 * @return void
 */
void matrix_rotateZ(Matrix *m, double cth, double sth);

/**
 * Rotate the matric m by an XYZ-axis rotation matrix parameterized by the vectors
 * ~u, ~v, and w~, where the three vectors represent an orthonormal 3D basis.
 * 
 * @param m the matrix to rotate
 * @param u the first column of the rotation matrix
 * @param v the second column of the rotation matrix
 * @param w the third column of the rotation matrix
 * 
 * @return void
 */
void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w);

/**
 * Shear the matrix by the Z axis.
 * 
 * @param m the matrix to shear
 * @param sx the x shear factor
 * @param sy the y shear factor
 * 
 * @return void
 */
void matrix_shearZ(Matrix *m, double sx, double sy);

/**
 * Compute the matrix m multiplied by the perspective matrix parameterized
 * by d.
 * 
 * @param m the matrix the multiply
 * @param d the parameter for the persepective matrix
 * 
 * @return void
 */
void matrix_perspective(Matrix *m, double d);

#endif

