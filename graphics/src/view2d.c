/**
 * Greg Attra
 * 10/18/2021
 * 
 * Executable for generating a gif in 2D where the view zooms and pans.
 */

#include "graphics.h"

Color White = {1.0, 1.0, 1.0};
Color Gray = {0.25, 0.25, 0.25};
Color Red = {1.0, 0.0, 0.0};

int world_size = 100;

static void draw_car(Image *src, Matrix *vtm)
{
    Point car_points[8];
    point_set2D(&car_points[0], 2, 7);
    point_set2D(&car_points[1], 2, 6);
    point_set2D(&car_points[2], 8, 6);
    point_set2D(&car_points[3], 8, 7);
    point_set2D(&car_points[4], 7, 7);
    point_set2D(&car_points[5], 6, 8);
    point_set2D(&car_points[6], 4, 8);
    point_set2D(&car_points[7], 3, 7);

    Polygon *car_pgon;
    car_pgon = polygon_createp(8, car_points);
    matrix_xformPolygon(vtm, car_pgon);

    polygon_draw(car_pgon, src, White);
}

static void draw_grid(Image *src, Matrix *vtm)
{
    for (int i = -world_size; i < world_size; i++)
    {
        Line h;
        point_set2D(&h.a, -world_size, i);
        point_set2D(&h.b, world_size, i);

        Line v;
        point_set2D(&v.a, i, -world_size);
        point_set2D(&v.b, i, world_size);

        matrix_xformLine(vtm, &h);
        matrix_xformLine(vtm, &v);

        line_draw(&h, src, Gray);
        line_draw(&v, src, Gray);
    }

    Point c;
    point_set2D(&c, 0.0, 0.0);

    matrix_xformPoint(vtm, &c, &c);

    Circle center;
    circle_set(&center, c, 10.0);

    circle_drawFill(&center, src, Red);
}


int main(int argc, char* argv[])
{
    int rows = 900;
    int cols = 1200;
    Image *src;
    src = image_create(rows, cols);
    
    View2D view;
    view.screenx = cols;
    view.screeny = rows;
    view.dx = 15.0;

    Point vrp;
    point_set2D(&vrp, 2.0, 10.0);
    point_copy(&view.vrp, &vrp);

    Vector x_axis;
    vector_set(&x_axis, 1.0, 0.0, 0.0);
    vector_copy(&view.x, &x_axis);

    Matrix vtm;
    matrix_setView2D(&vtm, &view);

    draw_grid(src, &vtm);
    draw_car(src, &vtm);

    image_write(src, "output/lab5/view2D.ppm");
}
