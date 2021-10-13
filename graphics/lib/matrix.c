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
    for (int i = 0; i < 4; i++)
    {
        double ax = a->m[i][0];
        double ay = a->m[i][1];
        double az = a->m[i][2];
        double ah = a->m[i][4];

        for (int j = 0; j < 4; j++)
        {
            double bx = b->m[0][j];
            double by = b->m[1][j];
            double bz = b->m[2][j];
            double bh = b->m[3][j];

            double cv = (ax*bx) + (ay*by) + (az*bz) + (ah*bh);

            matrix_set(c, i, j, cv);
        }
    }
}

void matrix_xformPoint(Matrix *m, Point *p, Point *q);

void matrix_xformVector(Matrix *m, Vector *p, Vector *q);

void matrix_xformPolygon(Matrix *m, Polygon *p);

void matrix_xformPolyline(Matrix *m, Polyline *p);

void matrix_xfromLine(Matrix *m, Line *l);

void matrix_scale2D(Matrix *m, double sx, double sy);

void matrix_translate2D(Matrix *m, double tx, double ty);

void matrix_shear2D(Matrix *m, double sx, double sy);

void matrix_translate(Matrix *m, double tx, double ty, double tz);

void matrix_scale(Matrix *m, double sx, double sy, double sz);

void matrix_rotateX(Matrix *m, double cth, double sth);

void matrix_rotateY(Matrix *m, double cth, double sth);

void matrix_rotateZ(Matrix *m, double cth, double sth);

void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w);

void matrix_shearZ(Matrix *m, double sx, double sy);

void matrix_perspective(Matrix *m, double d);
