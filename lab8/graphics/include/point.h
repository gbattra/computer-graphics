/**
 * Greg Attra
 * 09/30/2021
 * 
 * Header file for Point struct and API.
 */

#ifndef POINT
#define POINT

#include "stdio.h"
#include "image.h"
#include <stdio.h>

typedef struct
{
    double val[4];
} Point;

/**
 * Sets the first two values of the vector to x and y.
 * Sets the third value to 0.0 and the fourth value to 1.0.
 * 
 * @param p the point to set
 * @param x the first val to set
 * @param y the second value to set
 * 
 * @return void
 */
void point_set2D(Point *p, double x, double y);

/**
 * Sets the x,y and z coords. Homogenous coord is set to 1.0
 * 
 * @param p the point to set
 * @param x the first val to set
 * @param y the second val to set
 * @param z the third val to set
 * 
 * @return void
 */
void point_set3D(Point *p, double x, double y, double z);

/**
 * Sets the x,y, z and h coords on the point
 * 
 * @param p the point to set
 * @param x the first val to set
 * @param y the second val to set
 * @param z the third val to set
 * @param h the homogenous val to set
 * 
 * @return void
 */
void point_set(Point *p, double x, double y, double z, double h);

/**
 * Normalizes the point using the homogenous coord.
 * 
 * @param p the point to normalize
 * 
 * @return void
 */
void point_normalize(Point *p);

/**
 * Normalizes the point (including z) using the homogenous coord.
 * 
 * @param p the point to normalize
 * 
 * @return void
 */
void point_normalize_z(Point *p);


/**
 * Copies one point to another.
 * 
 * @param to the point to copy to
 * @param from the point to copy from
 * 
 * @return void
 */
void point_copy(Point *to, Point *from);

/**
 * Draws a pixel on the image given a point.
 * 
 * @param p the point on the image
 * @param src the image to draw on
 * @param c the pixel to draw
 * 
 * @return void
 */
void point_draw(Point *p, Image *src, FPixel c);

/**
 * Print the contents of the point to the filepointer.
 * 
 * @param p the point to print
 * @param fp the file to print to
 * 
 * @return void
 */
void point_print(Point *p, FILE *fp);

/**
 * Copy a list of points into another list of points.
 * 
 * @param to_plist the target list
 * @param from_plist the source list
 * @param n_points the size of the lists
 * 
 * @return void
 */
void point_copyList(Point *to_plist, Point *from_plist, int n_points);

/**
 * Project a point a given distance from a center point.
 * 
 * @param p the point to project
 * @param cp the center point to project from
 * @param d the distance to project
 * @param dst the resulting point
 * 
 * @return void
 */
void point_project(Point *p, Point *cp, float d, Point *dst);

#endif
