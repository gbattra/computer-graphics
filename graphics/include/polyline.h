/**
 * Greg Attra
 * 10/04/2021
 * 
 * Header file defining polyline API.
 */

#include "point.h"
#include "image.h"


typedef struct
{
    int zBuffer;
    int numVertex;
    Point *vertex;
} Polyline;

/**
 * Returns an allocated Polyline pointer initialized so that numVertex
 * is 0 and vertex is NULL.
 * 
 * @return allocated polyline pointer
 */
Polyline *polyline_create();

/**
 * Returns an allocated Polyline pointer with the vertex list initialized
 * to the points in vlist.
 * 
 * @param numV the number of vertices
 * @param vlist the number of points
 * 
 * @return the allocated polyline pointer
 */
Polyline *polyline_createp(int numV, Point *vlist);

/**
 * Frees the internal data and polyline pointer.
 * 
 * @param pline the polyline to free
 * 
 * @return void
 */
void polyline_free(Polyline *pline);

/**
 * Initializes the preexisting polyline to an empty polyline.
 * 
 * @param pline the polyine to initialize
 * 
 * @return void
 */
void polyline_init(Polyline *pline);

/**
 * Initializes the vertex list to the points in vlist.
 * De-allocates/allocates the vertex list for p, as necessary.
 * 
 * @param pline the polyline to update
 * @param numV the number of vertices in the list
 * @param vlist the list of vertex points
 * 
 * @return void
 */
void polyline_set(Polyline *pline, int numV, Point *vlist);

/**
 * Frees the internal data in the polyline and resets values to defaults.
 * 
 * @param pline the polyline to clear
 * 
 * @return void
 */
void polyline_clear(Polyline *pline);

/**
 * Sets the zBuffer flag on the polyline.
 * 
 * @param pline the polyline to update
 * @param flag the zbuffer flag value
 * 
 * @return void
 */
void polyline_zBuffer(Polyline *pline, int flag);

/**
 * Copies one polyline to another.
 * 
 * @param to the target polyline
 * @param from the source polyline
 * 
 * @return void
 */
void polyline_copy(Polyline *to, Polyline *from);

/**
 * Prints the polyline to the file.
 * 
 * @param pline the polyline to print
 * @param fp the file pointer to print to
 * 
 * @return void
 */
void polyline_print(Polyline *pline, FILE *fp);

/**
 * Normalize the x and y values of the vertex by the homogenous coord.
 * 
 * @param pline the polyline to normalize
 * 
 * @return void
 */
void polyline_normalize(Polyline *pline);

/**
 * Draws the polyline on the image in the given color.
 * 
 * @param pline the polyline to draw
 * @param src the image to draw on
 * @param c the color of the polyine
 * 
 * @return void
 */
void polyline_draw(Polyline *pline, Image *src, Color c);
