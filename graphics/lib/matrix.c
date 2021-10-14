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

        for (int j = 0; j < 4; j++)
        {
            double bx = b->m[0][j];
            double by = b->m[1][j];
            double bz = b->m[2][j];
            double bh = b->m[3][j];

            double cv = (ax*bx) + (ay*by) + (az*bz) + (ah*bh);

            matrix_set(&tmp, i, j, cv);
        }
    }
    matrix_copy(c, &tmp);
}

void matrix_xformPoint(Matrix *m, Point *p, Point *q)
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

        double cv = (ax*px) + (ay*py) + (az*pz) + (ah*ph);

        q->val[i] = cv;
    }
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

        double cv = (ax*px) + (ay*py) + (az*pz) + (ah*ph);

        q->val[i] = cv;
    }
}

void matrix_xformPolygon(Matrix *m, Polygon *p)
{
    for (int i = 0; i < p->nVertex; i++)
    {
        Point q;
        matrix_xformPoint(m, &p->vlist[i], &q);
        point_copy(&p->vlist[i], &q);

        // do same for normals using matrix_xformVector()
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

void matrix_xfromLine(Matrix *m, Line *l)
{
    Point ta, tb;
    matrix_xformPoint(m, &l->a, &ta);
    matrix_xformPoint(m, &l->b, &tb);
    point_copy(&l->a, &ta);
    point_copy(&l->b, &tb);
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
    matrix_set(&R, 1, 0, u->val[1]);
    matrix_set(&R, 2, 0, u->val[2]);
    matrix_set(&R, 3, 0, u->val[3]);

    matrix_set(&R, 0, 1, v->val[0]);
    matrix_set(&R, 1, 1, v->val[1]);
    matrix_set(&R, 2, 1, v->val[2]);
    matrix_set(&R, 3, 1, v->val[3]);

    matrix_set(&R, 0, 2, w->val[0]);
    matrix_set(&R, 1, 2, w->val[1]);
    matrix_set(&R, 2, 2, w->val[2]);
    matrix_set(&R, 3, 2, w->val[3]);

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
    matrix_set(&P, 3, 2, 1.0/d);

    matrix_multiply(&P, m, m);
}
