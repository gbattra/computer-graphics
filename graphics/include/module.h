/**
 * Greg Attra
 * 10/23/2021
 * 
 * Header file defining Module API.
 */

#ifndef MODULE
#define MODULE

#include "point.h"
#include "line.h"
#include "polyline.h"
#include "polygon.h"

typedef enum {
  ObjNone,
  ObjLine,
  ObjPoint,
  ObjPolyline,
  ObjPolygon,
  ObjIdentity,
  ObjMatrix,
  ObjColor,
  ObjBodyColor,
  ObjSurfaceColor,
  ObjSurfaceCoeff,
  ObjLight,
  ObjModule
} ObjectType;

typedef union {
  Point point;
  Line  line;
  Polyline polyline;
  Polygon polygon;
  Matrix matrix;
  Color color;
  float coeff;
  void *module;
} Object;

typedef struct {
  ObjectType type;
  Object obj;
  void *next;
} Element;

typedef struct {
    Element *head;
    Element *tail;
} Module;

/**
 * Allocate and initialize an empty element.
 * 
 * @return a pointer to the allocated element
 */
Element *element_create(void);

/**
 * Initialize an element and store a copy of the data pointed to by obj.
 * 
 * @param type enum indicating the type of data stored at obj
 * @param obj the data to configure the element
 * 
 * @return an initialized element with the obj's data
 */
Element *element_init(ObjectType type, void *obj);

/**
 * Deallocate and free the element.
 * 
 * @param el the element to delete
 * 
 * @return void
 */
void element_delete(Element *el);

/**
 * Allocate and initialize and empty module.
 * 
 * @return the initialized module
 */
Module *module_create(void);

/**
 * Clear the modules list of elements.
 * 
 * @param md the module to clear
 * 
 * @return void
 */
void module_clear(Module *md);

/**
 * Free the elements in the module and the module pointer itself.
 * 
 * @param md the module to delete
 *
 * @return void
 */
void module_delete(Module *md);

/**
 * Insert an element into the tail of the module list.
 * 
 * @param md the module to insert into
 * @param el the element to insert
 * 
 * @return void
 */
void module_insert(Module *md, Element *el);

/**
 * Adds a pointer to a sub module to the tail of the module list.
 * 
 * @param md the parent module
 * @param sub the submodule to insert
 * 
 * @return void
 */
void module_module(Module *md, Module *sub);

/**
 * Adds the point to the tail of the module list.
 * 
 * @param md the module to insert into
 * @param p the point to insert
 * 
 * @return void
 */
void module_point(Module *md, Point *p);

/**
 * Adds the line to the tail of the module list.
 * 
 * @param md the module to insert into
 * @param l the line to insert
 * 
 * @return void
 */
void module_line(Module *md, Line *l);

/**
 * Adds the polygon to the tail of the module list.
 * 
 * @param md the module to insert into
 * @param pl the polyline to insert
 * 
 * @return void
 */
void module_polyline(Module *md, Polyline *pl);

/**
 * Adds the polygon to the tail of the module list.
 * 
 * @param md the module to insert into
 * @param pgon the polygon to insert
 * 
 * @return void
 */
void module_polygon(Module *md, Polygon *pgon);

/**
 * Adds an identity matrix set to the current transformation matrix at end
 * of module list.
 * 
 * @param md the module to insert into
 * 
 * @return void
 */
void module_identity(Module *md);

/**
 * Adds a translation 2D matrix to the tail of the module list.
 * 
 * @param md the module to insert into
 * @param tx the x translation
 * @param ty the y translation
 * 
 * @return void
 */
void module_translate2D(Module *md, double tx, double ty);

/**
 * Adds a scale 2D matrix to the end of the module list.
 * 
 * @param md the module to insert into
 * @param sx the x scale factor
 * @param sy the y scale factor
 * 
 * @return void
 */
void module_scale2D(Module *md, double sx, double sy);

/**
 * Adds a z-rotation matrix to the end of the module list.
 * 
 * @param md the module to insert into
 * @param cth the cos(theta) value
 * @param sth the sin(theta) value
 * 
 * @return void
 */
void module_rotateZ(Module *md, double cth, double sth);

/**
 * Adds a shear 2D matrix to the end of the module list.
 * 
 * @param md the module to insert into
 * @param shx the x shear factor
 * @param shy the y shear factor
 * 
 * @return void
 */
void module_shear2D(Module *md, double shx, double shy);

#endif
