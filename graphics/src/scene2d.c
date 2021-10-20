/**
 * Greg Attra
 * 10/20/2021
 * 
 * Simple two scene demonstrating the View2D API capabilities.
 */

#include "graphics.h"

int nCircles = 10;
double delta = 3;

static void draw_circles(Image *src, Matrix *vtm, Color *cols)
{
    Circle c;
    double r = delta * nCircles;
    Point tc;
    point_set2D(&tc, delta * nCircles, 0);

    for (int i = nCircles; i > 0; i--)
    {
        circle_set(&c, tc, r);
        matrix_xformCircle(vtm, &c);
        
        circle_drawFill(&c, src, cols[i]);

        r -= delta;
        point_set2D(&tc, tc.val[0] - delta, tc.val[1]);
    }
}


int main(int argc, char *argv[])
{
    Color colors[nCircles];
    for (int c = 0; c < nCircles; c++)
    {
        Color color;
        color_random(&color);
        color_copy(&colors[c], &color);
    }

    char filename[256];
    int nframes = 20;
    int rows = 600;
    int cols = 900;

    Image *src;
    src = image_create(rows, cols);

    double dx = 10.0;
    Point vrp;
    point_set2D(&vrp, -10, 0);
    Vector x_axis;
    vector_set(&x_axis, 1.0, 0.0, 0.0);

    double pan_step = 2.5;
    double zoom_step = 5;
    
    for (int i = 0; i < nframes; i++)
    {
        View2D view;
        view.screenx = cols;
        view.screeny = rows;
        view.dx = dx;
        point_copy(&view.vrp, &vrp);
        vector_copy(&view.x, &x_axis);

        Matrix vtm;
        matrix_setView2D(&vtm, &view);

        image_reset(src);

        draw_circles(src, &vtm, colors);

        sprintf(filename, "output/lab5/scene2D/frame-%04d.ppm", i);
        image_write(src, filename);

        dx += zoom_step;
        point_set2D(&vrp, vrp.val[0] + pan_step, vrp.val[1]);
    }

    image_free(src);

    return 0;
}
