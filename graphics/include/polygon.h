/**
 * Greg Attra
 * 10/06/2021
 * 
 * Definition of the polygon API.
 */

#ifndef POLYGON
#define POLYGON

#include "image.h"
#include "point.h"
#include "geometry.h"
#include <stdlib.h>

typedef struct
{
    int oneSided;
    int nVertex;
    int zBuffer;
    Point *vlist;
    Color *clist;
    Vector *nlist;
} Polygon;

/**
 * Returns an allocated Polygon pointer initialized so that numVertex is 0 and
 * vertex is NULL.
 * 
 * @return initialized polygon
 */
Polygon *polygon_create(void);

/**
 * Returns an allocated Polygon pointer with the vertex list initialized to a
 * copy of the points in vlist.
 * 
 * @param nVertex the number of points in the polygon
 * @param vlist the list of points
 * 
 * @return initialized polygon
 */
Polygon *polygon_createp(int nVertex, Point *vlist);

/**
 * Frees the internal data for a Polygon and the Polygon pointer.
 * 
 * @param pgon the polygon to free
 * 
 * @return void
 */
void polygon_free(Polygon *pgon);

/**
 * Initializes the existing Polygon to an empty Polygon.
 * 
 * @param pgon
 * 
 * @return void
 */
void polygon_init(Polygon *pgon);

/**
 * Initializes the vertex array to the points in vlist.
 * 
 * @param pgon the polygon to set
 * @param numV the number of vertices
 * @param vlist the list of vertices
 * 
 * @return void
 */
void polygon_set(Polygon *pgon, int numV, Point *vlist);

/**
 * Frees the internal data and resets the fields.
 * 
 * @param pgon the polygon to free
 * 
 * @return void
 */
void polygon_clear(Polygon *pgon);

/**
 * Sets the oneSided field to the value.
 * 
 * @param pgon the polygon to set
 * @param oneSided the value to set
 * 
 * @return void
 */
void polygon_setSided(Polygon *pgon, int oneSided);

/**
 * Sets the color list on the polygon.
 * 
 * @param pgon the polygon to set
 * @param numV the number of vertices in the polygon
 * @param clist the list of colors
 * 
 * @return void
 */
void polygon_setColors(Polygon *pgon, int numV, Color *clist);

/**
 * Initializes the normal array to the vectors in nlist.
 * 
 * @param pgon the polygon to set
 * @param numV the number of normals in the list
 * @param nlist the normals list
 * 
 * @return void
 */
void polygon_setNormals(Polygon *pgon, int numV, Vector *nlist);

/**
 * Sets all the properties of the polygon.
 * 
 * @param pgon the polygon to set
 * @param numV the number of vertices in the polygon
 * @param vlist the list of vertices
 * @param clist the list of colors
 * @param nlist the list of normals
 * @param zBuffer the zbuffer flag value
 * @param oneSided the oneSided flag value
 * 
 * @return void
 */
void polygon_setAll(
    Polygon *pgon,
    int numV,
    Point *vlist,
    Color *clist,
    Vector *nlist,
    int zBuffer,
    int oneSided);

/**
 * Sets the zbuffer flag on the polygon.
 * 
 * @param pgon the polygon to update
 * @param flag the zbuffer flag value
 * 
 * @return void
 */
void polygon_zBuffer(Polygon *pgon, int flag);

/**
 * Copies one polygon to another.
 * 
 * @param to the polygon to copy to
 * @param from the polygon to copy from
 * 
 * @return void
 */
void polygon_copy(Polygon *to, Polygon *from);

/**
 * Prints the polygon to the filepointer.
 * 
 * @param pgon the polygon to print
 * @param fp the filepointer to print to
 * 
 * @return void
 */
void polygon_print(Polygon *pgon, FILE *fp);

/**
 * Normalizes the polygon.
 * 
 * @param pgon the polygon to normalize
 * 
 * @return void
 */
void polygon_normalize(Polygon *pgon);

/**
 * Draws the polygon outline on the image.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw on
 * @param c the color of the polygon
 * 
 * @return void
 */
void polygon_draw(Polygon *pgon, Image *src, Color c);

/**
 * Draws and fills the polygon on the image.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw on
 * @param c the color of the polygon
 * 
 * @return void
 */
void polygon_drawFill(Polygon *pgon, Image *src, Color c);

/**
 * Draws and fills the polygon using the barycentric coordinates.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw
 * @param color the color to use
 * 
 * @return void
 */
void polygon_drawFillB(Polygon *pgon, Image *src, Color color);

/**
 * Fill a polygon with a gradient from one color to another.
 * 
 * @param pgon the polygon to draw
 * @param src the image to draw on
 * @param ca the start color
 * @param cb the end color
 * @param vert flag for vertical gradient (0 = horizontal by default)
 * 
 * @return void
 */
void polygon_drawFillG(Polygon *pgon, Image *src, Color ca, Color cb, int vert);

/**
 * Gets the furthest point right.
 * 
 * @param pgon the polygon to search
 * 
 * @return the furthest right point
 */
Point *polygon_maxX(Polygon *pgon);

/**
 * Gets the furthest point left.
 * 
 * @param pgon the polygon to search
 * 
 * @return the furthest left point
 */
Point *polygon_minX(Polygon *pgon);

// void polygon_drawShade(Polygon *pgon, Image *src, DrawState *ds, Lighting *light);

// void polygon_shade(Polygon *pgon, Image *src, DrawState *ds, Lighting *light);

#endif