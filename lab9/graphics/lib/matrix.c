/**
 * Greg Attra
 * 10/12/2021
 * 
 * Implementation of the Matrix API defined in matrix.h
 */

/**
 * Greg Attra
 * 10/12/2021
 * 
 * Definition of the Matrix struct and API.
 */

#include "matrix.h"
#include <math.h>

void matrix_print(Matrix *m, FILE *fp)
{
    fprintf(
        fp,
        "[ %f  %f  %f  %f  \n"
        "  %f  %f  %f  %f  \n"
        "  %f  %f  %f  %f  \n"
        "  %f  %f  %f  %f ]\n",
        m->m[0][0], m->m[0][1], m->m[0][2], m->m[0][3],
        m->m[1][0], m->m[1][1], m->m[1][2], m->m[1][3],
        m->m[2][0], m->m[2][1], m->m[2][2], m->m[2][3],
        m->m[3][0], m->m[3][1], m->m[3][2], m->m[3][3]);
}

void matrix_clear(Matrix *m)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix_set(m, i, j, 0.0);
        }
    }
}

void matrix_identity(Matrix *m)
{
    matrix_clear(m);
    matrix_set(m, 0, 0, 1.0);
    matrix_set(m, 1, 1, 1.0);
    matrix_set(m, 2, 2, 1.0);
    matrix_set(m, 3, 3, 1.0);
}

double matrix_get(Matrix *m, int i, int j)
{
    return m->m[i][j];
}

void matrix_set(Matrix *m, int i, int j, double v)
{
    m->m[i][j] = v;
}

void matrix_copy(Matrix *to, Matrix *from)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix_set(to, i, j, from->m[i][j]);
        }
    }
}

void matrix_transpose(Matrix *m)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j) continue;
            double a = m->m[i][j];
            double b = m->m[j][i];
            m->m[i][j] = b;
            m->m[j][i] = a;
        }
    }
}

void matrix_multiply(Matrix *a, Matrix *b, Matrix *c)
{
    Matrix tmp;
    for (int i = 0; i < 4; i++)
    {
        double ax = a->m[i][0];
        double ay = a->m[i][1];
        double az = a->m[i][2];
        double ah = a->m[i][3];

        // if (ax == -0.0) ax = 0.0;
        // if (ay == -0.0) ay = 0.0;
        // if (az == -0.0) az = 0.0;
        // if (ah == -0.0) ah = 0.0;

        for (int j = 0; j < 4; j++)
        {
            double bx = b->m[0][j];
            double by = b->m[1][j];
            double bz = b->m[2][j];
            double bh = b->m[3][j];

            // if (bx == -0.0) bx = 0.0;
            // if (by == -0.0) by = 0.0;
            // if (bz == -0.0) bz = 0.0;
            // if (bh == -0.0) bh = 0.0;

            double cv = (ax*bx) + (ay*by) + (az*bz) + (ah*bh);

            matrix_set(&tmp, i, j, cv);
        }
    }
    matrix_copy(c, &tmp);
}

void matrix_xformPoint(Matrix *m, Point *p, Point *q)
{
    Point tmp;
    for (int i = 0; i < 4; i++)
    {
        double ax = m->m[i][0];
        double ay = m->m[i][1];
        double az = m->m[i][2];
        double ah = m->m[i][3];

        double px = p->val[0];
        double py = p->val[1];
        double pz = p->val[2];
        double ph = p->val[3];

        // if (ax == -0.0) ax = 0.0;
        // if (ay == -0.0) ay = 0.0;
        // if (az == -0.0) az = 0.0;
        // if (ah == -0.0) ah = 0.0;

        // if (px == -0.0) px = 0.0;
        // if (py == -0.0) py = 0.0;
        // if (pz == -0.0) pz = 0.0;
        // if (ph == -0.0) ph = 0.0;

        double cv = (ax*px) + (ay*py) + (az*pz) + (ah*ph);

        tmp.val[i] = cv;
    }

    point_copy(q, &tmp);
}

void matrix_xformVector(Matrix *m, Vector *p, Vector *q)
{
    for (int i = 0; i < 4; i++)
    {
        double ax = m->m[i][0];
        double ay = m->m[i][1];
        double az = m->m[i][2];
        double ah = m->m[i][3];

        double px = p->val[0];
        double py = p->val[1];
        double pz = p->val[2];
        double ph = p->val[3];

        // if (ax == -0.0) ax = 0.0;
        // if (ay == -0.0) ay = 0.0;
        // if (az == -0.0) az = 0.0;
        // if (ah == -0.0) ah = 0.0;

        // if (px == -0.0) px = 0.0;
        // if (py == -0.0) py = 0.0;
        // if (pz == -0.0) pz = 0.0;
        // if (ph == -0.0) ph = 0.0;

        double cv = (ax*px) + (ay*py) + (az*pz) + (ah*ph);

        q->val[i] = cv;
    }
}

void matrix_xformPolygon(Matrix *m, Polygon *p)
{
    for (int i = 0; i < p->nVertex; i++)
    {
        matrix_xformPoint(m, &p->vlist[i], &p->vlist[i]);
        matrix_xformVector(m, &p->nlist[i], &p->nlist[i]);
    }
}

void matrix_xformPolyline(Matrix *m, Polyline *p)
{
    for (int i = 0; i < p->numVertex; i++)
    {
        Point q;
        matrix_xformPoint(m, &p->vertex[i], &q);
        point_copy(&p->vertex[i], &q);
    }
}

void matrix_xformLine(Matrix *m, Line *l)
{
    Point ta, tb;
    matrix_xformPoint(m, &l->a, &ta);
    matrix_xformPoint(m, &l->b, &tb);
    point_copy(&l->a, &ta);
    point_copy(&l->b, &tb);
}

void matrix_xformCircle(Matrix *m, Circle *c)
{
    Point radius;
    point_set2D(&radius, c->center.val[0] - c->radius, c->center.val[1] - c->radius);
    matrix_xformPoint(m, &c->center, &c->center);
    matrix_xformPoint(m, &radius, &radius);

    double r = fabs(radius.val[0] - c->center.val[0]);
    c->radius = r;
}

void matrix_xformElipse(Matrix *m, Elipse *e)
{
    Point ra, rb;
    point_set2D(&ra, e->c.val[0] - e->ra, e->c.val[1] - e->ra);
    point_set2D(&rb, e->c.val[0] - e->rb, e->c.val[1] - e->rb);

    matrix_xformPoint(m, &e->c, &e->c);
    matrix_xformPoint(m, &ra, &ra);
    matrix_xformPoint(m, &rb, &rb);

    elipse_set(
        e,
        e->c,
        fabs(ra.val[0] - e->c.val[0]),
        fabs(rb.val[1] - e->c.val[1]),
        0);
}

void matrix_xformCube(Matrix *m, Cube *c)
{
    matrix_xformPoint(m, &c->c, &c->c);
    for (int i = 0; i < 6; i++)
    {
        matrix_xformPolygon(m, &c->sides[i]);
    }
}

void matrix_scale2D(Matrix *m, double sx, double sy)
{
    Matrix S;
    matrix_identity(&S);
    matrix_set(&S, 0, 0, sx);
    matrix_set(&S, 1, 1, sy);

    matrix_multiply(&S, m, m);
}

void matrix_translate2D(Matrix *m, double tx, double ty)
{
    Matrix T;
    matrix_identity(&T);
    matrix_set(&T, 0, 3, tx);
    matrix_set(&T, 1, 3, ty);

    matrix_multiply(&T, m, m);
}

void matrix_shear2D(Matrix *m, double sx, double sy)
{
    Matrix S;
    matrix_identity(&S);
    matrix_set(&S, 0, 1, sx);
    matrix_set(&S, 1, 0, sy);

    matrix_multiply(&S, m, m);
}

void matrix_translate(Matrix *m, double tx, double ty, double tz)
{
    Matrix T;
    matrix_identity(&T);
    matrix_set(&T, 0, 3, tx);
    matrix_set(&T, 1, 3, ty);
    matrix_set(&T, 2, 3, tz);

    matrix_multiply(&T, m, m);
}

void matrix_scale(Matrix *m, double sx, double sy, double sz)
{
    Matrix S;
    matrix_identity(&S);
    matrix_set(&S, 0, 0, sx);
    matrix_set(&S, 1, 1, sy);
    matrix_set(&S, 2, 2, sz);

    matrix_multiply(&S, m, m);
}

void matrix_rotateX(Matrix *m, double cth, double sth)
{
    Matrix R;
    matrix_identity(&R);
    matrix_set(&R, 1, 1, cth);
    matrix_set(&R, 1, 2, -sth);
    matrix_set(&R, 2, 1, sth);
    matrix_set(&R, 2, 2, cth);

    matrix_multiply(&R, m, m);
}

void matrix_rotateY(Matrix *m, double cth, double sth)
{
    Matrix R;
    matrix_identity(&R);
    matrix_set(&R, 0, 0, cth);
    matrix_set(&R, 0, 2, sth);
    matrix_set(&R, 2, 0, -sth);
    matrix_set(&R, 2, 2, cth);

    matrix_multiply(&R, m, m);
}

void matrix_rotateZ(Matrix *m, double cth, double sth)
{
    Matrix R;
    matrix_identity(&R);
    matrix_set(&R, 0, 0, cth);
    matrix_set(&R, 0, 1, -sth);
    matrix_set(&R, 1, 0, sth);
    matrix_set(&R, 1, 1, cth);

    matrix_multiply(&R, m, m);
}

void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w)
{
    Matrix R;
    matrix_identity(&R);
    matrix_set(&R, 0, 0, u->val[0]);
    matrix_set(&R, 0, 1, u->val[1]);
    matrix_set(&R, 0, 2, u->val[2]);

    matrix_set(&R, 1, 0, v->val[0]);
    matrix_set(&R, 1, 1, v->val[1]);
    matrix_set(&R, 1, 2, v->val[2]);

    matrix_set(&R, 2, 0, w->val[0]);
    matrix_set(&R, 2, 1, w->val[1]);
    matrix_set(&R, 2, 2, w->val[2]);

    matrix_multiply(&R, m, m);
}

void matrix_shearZ(Matrix *m, double sx, double sy)
{
    Matrix S;
    matrix_identity(&S);
    matrix_set(&S, 0, 2, sx);
    matrix_set(&S, 1, 2, sy);

    matrix_multiply(&S, m, m);
}

void matrix_perspective(Matrix *m, double d)
{
    Matrix P;
    matrix_identity(&P);
    matrix_set(&P, 3, 3, 0.0);
    matrix_set(&P, 3, 2, 1.0/d);

    matrix_multiply(&P, m, m);
}

void matrix_xformBezierCurve(Matrix *m, BezierCurve *source, BezierCurve *target)
{
    for (int i = 0; i < 4; i++)
    {
        matrix_xformPoint(m, &source->vlist[i], &target->vlist[i]);
    }
}
