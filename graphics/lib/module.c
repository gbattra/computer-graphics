/**
 * Greg Attra
 * 10/24/2021
 * 
 * Implementation of the module API defined in module.h
 */

#include "image.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "polyline.h"
#include "polygon.h"
#include "cube.h"
#include "matrix.h"
#include "module.h"
#include <stdio.h>
#include "list.h"

/**
 * Allocate and initialize an empty element.
 * 
 * @return a pointer to the allocated element
 */
Element *element_create(void)
{
    Element *el = (Element *) malloc(sizeof(Element));
    el->next = NULL;
    el->type = ObjNone;
    return el;
}

Element *element_init(ObjectType type, void *obj)
{
    Element *el = element_create();
    el->type = type;
    switch(type)
    {
        case ObjLine:
            line_copy(&el->obj.line, obj);
            break;
        case ObjPoint:
            point_copy(&el->obj.point, obj);
            break;
        case ObjPolyline:
            polyline_copy(&el->obj.polyline, obj);
            break;
        case ObjPolygon:
            polygon_copy(&el->obj.polygon, obj);
            break;
        case ObjIdentity:
            matrix_identity(&el->obj.matrix);
            break;
        case ObjMatrix:
            matrix_copy(&el->obj.matrix, obj);
            break;
        case ObjColor:
            color_copy(&el->obj.color, obj);
            break;
        case ObjBodyColor:
            color_copy(&el->obj.color, obj);
            break;
        case ObjSurfaceColor:
            color_copy(&el->obj.color, obj);
            break;
        case ObjSurfaceCoeff:
            el->obj.coeff = *(float*) obj;
            break;
        case ObjModule:
            el->obj.module = obj;
            break;
        default:
            break;
    }
    return el;
}

void element_delete(Element *el)
{
    if (el->next) element_delete(el->next);
    free(el);
}

Module *module_create(void)
{
    Module *mod = (Module *) malloc(sizeof(Module));
    mod->head = element_create();
    mod->tail = mod->head;
    return mod;
}

void module_clear(Module *md)
{
    Element *el = md->head;
    element_delete(el);
    md->head = element_create();
    md->tail = md->head;
}

void module_delete(Module *md)
{
    module_clear(md);
    free(md);
}

void module_insert(Module *md, Element *el)
{
    md->tail->next = element_init(el->type, &el->obj);
    md->tail = md->tail->next;
}

void module_module(Module *md, Module *sub)
{
    md->tail->next = element_init(ObjModule, sub);
    md->tail = md->tail->next;
}

void module_point(Module *md, Point *p)
{
    md->tail->next = element_init(ObjPoint, p);
    md->tail = md->tail->next;
}

void module_line(Module *md, Line *l)
{
    md->tail->next = element_init(ObjLine, l);
    md->tail = md->tail->next;
}

void module_polyline(Module *md, Polyline *pl)
{
    md->tail->next = element_init(ObjPolyline, pl);
    md->tail = md->tail->next;
}

void module_polygon(Module *md, Polygon *pgon)
{
    md->tail->next = element_init(ObjPolygon, pgon);
    md->tail = md->tail->next;
}

void module_identity(Module *md)
{
    md->tail->next = element_init(ObjIdentity, NULL);
    md->tail = md->tail->next;
}

void module_translate2D(Module *md, double tx, double ty)
{
    Matrix m;
    matrix_identity(&m);
    matrix_translate2D(&m, tx, ty);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_scale2D(Module *md, double sx, double sy)
{
    Matrix m;
    matrix_identity(&m);
    matrix_scale2D(&m, sx, sy);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_rotateZ(Module *md, double cth, double sth)
{
    Matrix m;
    matrix_identity(&m);
    matrix_rotateZ(&m, cth, sth);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_shear2D(Module *md, double shx, double shy)
{
    Matrix m;
    matrix_identity(&m);
    matrix_shear2D(&m, shx, shy);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_translate(Module *md, double tx, double ty, double tz)
{
    Matrix m;
    matrix_identity(&m);
    matrix_translate(&m, tx, ty, tz);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_scale(Module *md, double sx, double sy, double sz)
{
    Matrix m;
    matrix_identity(&m);
    matrix_scale(&m, sx, sy, sz);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_rotateX(Module *md, double cth, double sth)
{
    Matrix m;
    matrix_identity(&m);
    matrix_rotateX(&m, cth, sth);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_rotateY(Module *md, double cth, double sth)
{
    Matrix m;
    matrix_identity(&m);
    matrix_rotateY(&m, cth, sth);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w)
{
    Matrix m;
    matrix_identity(&m);
    matrix_rotateXYZ(&m, u, v, w);
    md->tail->next = element_init(ObjMatrix, &m);
    md->tail = md->tail->next;
}

void module_cube(Module *md, int solid)
{
    Point c;
    point_set3D(&c, 0, 0, 0);

    Cube *cube;
    cube = cube_create(1, 1, 1, c);

    for (int p = 0; p < 6; p++)
    {
        module_polygon(md, &cube->sides[p]);
    }
}

void module_color(Module *md, Color c)
{
    md->tail->next = element_init(ObjColor, &c);
    md->tail = md->tail->next;
}

void module_bodyColor(Module *md, Color c)
{
    md->tail->next = element_init(ObjBodyColor, &c);
    md->tail = md->tail->next;
}

void module_surfaceColor(Module *md, Color c)
{
    md->tail->next = element_init(ObjSurfaceColor, &c);
    md->tail = md->tail->next;
}

void module_surfaceCoeff(Module *md, float sc)
{
    md->tail->next = element_init(ObjSurfaceCoeff, &sc);
    md->tail = md->tail->next;
}

void module_bezierCurve(Module *md, BezierCurve *bc, int n_divs)
{
    LinkedList *curves = ll_new();
    bezierCurve_divide(bc, curves, n_divs);

    BezierCurve *curr = (BezierCurve *) ll_pop(curves);
    while (curr)
    {
        for (int i = 0; i < 3; i++)
        {
            Line l;
            line_set2D(
                &l,
                curr->vlist[i].val[0],
                curr->vlist[i].val[1],
                curr->vlist[i+1].val[0],
                curr->vlist[i+1].val[1]);
            module_line(md, &l);
        }

        free(curr);
        curr = ll_pop(curves);
    }
}

void module_draw(
    Module *md,
    Matrix *vtm,
    Matrix *gtm,
    DrawState *ds,
    Lighting *light,
    Image *src)
{
    Matrix ltm;
    matrix_identity(&ltm);

    Element *el = md->head;
    while (el)
    {
        switch(el->type)
        {
            case ObjLine:
            {
                Line l;
                line_copy(&l, &el->obj.line);
                matrix_xformLine(&ltm, &l);
                matrix_xformLine(gtm, &l);
                matrix_xformLine(vtm, &l);
                line_normalize(&l);
                line_draw(&l, src, ds->color);
                break;
            }
            case ObjPoint:
            {
                Point p;
                point_copy(&p, &el->obj.point);
                matrix_xformPoint(&ltm, &p, &p);
                matrix_xformPoint(gtm, &p, &p);
                matrix_xformPoint(vtm, &p, &p);
                point_normalize(&p);
                FPixel pix;
                pix.rgb[0] = ds->color.c[0];
                pix.rgb[1] = ds->color.c[1];
                pix.rgb[2] = ds->color.c[2];
                point_draw(&p, src, pix);
                break;
            }
            case ObjPolyline:
            {
                Polyline *pline = polyline_create();
                polyline_copy(pline, &el->obj.polyline);
                matrix_xformPolyline(&ltm, pline);
                matrix_xformPolyline(gtm, pline);
                matrix_xformPolyline(vtm, pline);
                polyline_normalize(pline);
                polyline_draw(pline, src, ds->color);
                break;
            }
            case ObjPolygon:
            {
                Polygon *pgon = polygon_create();
                polygon_copy(pgon, &el->obj.polygon);
                matrix_xformPolygon(&ltm, pgon);
                matrix_xformPolygon(gtm, pgon);
                matrix_xformPolygon(vtm, pgon);
                polygon_normalize(pgon);
                if (ds->shade == ShadeFrame)
                {
                    polygon_draw(pgon, src, ds->color);
                }
                else if (ds->shade == ShadeConstant)
                {
                    polygon_drawFill(pgon, src, ds->color);
                }
                break;
            }
            case ObjIdentity:
                matrix_identity(&ltm);
                break;
            case ObjMatrix:
                matrix_multiply(&el->obj.matrix, &ltm, &ltm);
                break;
            case ObjColor:
                ds->color = el->obj.color;
                break;
            case ObjBodyColor:
                ds->body = el->obj.color;
                break;
            case ObjSurfaceColor:
                ds->surface = el->obj.color;
                break;
            case ObjSurfaceCoeff:
                ds->surfaceCoeff = el->obj.coeff;
                break;
            case ObjModule:
            {
                Matrix tmp_gtm;
                matrix_multiply(gtm, &ltm, &tmp_gtm);
                DrawState tmp_ds;
                drawstate_copy(&tmp_ds, ds);
                module_draw(el->obj.module, vtm, &tmp_gtm, &tmp_ds, light, src);
                break;
            }
            default:
                break;
        }
        el = el->next;
    }
}
