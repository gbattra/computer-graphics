/**
 * Greg Attra
 * 10/18/2021
 * 
 * Executable for generating a gif in 2D where the view zooms and pans.
 */

#include "graphics.h"
#include <math.h>

Color White = {1.0, 1.0, 1.0};
Color Gray = {0.25, 0.25, 0.25};
Color Red = {1.0, 0.0, 0.0};

int world_size = 100;

static void draw_car(Image *src, Matrix *vtm)
{
    Point car_points[8];
    point_set2D(&car_points[0], 2, 7 - .5);
    point_set2D(&car_points[1], 2, 6 - .5);
    point_set2D(&car_points[2], 8, 6 - .5);
    point_set2D(&car_points[3], 8, 7 - .5);
    point_set2D(&car_points[4], 7, 7 - .5);
    point_set2D(&car_points[5], 6, 8 - .5);
    point_set2D(&car_points[6], 4, 8 - .5);
    point_set2D(&car_points[7], 3, 7 - .5);

    Polygon *car_pgon;
    car_pgon = polygon_createp(8, car_points);
    matrix_xformPolygon(vtm, car_pgon);

    polygon_draw(car_pgon, src, White);
    polygon_free(car_pgon);

    Point wheel_centers[2];
    point_set2D(&wheel_centers[0], 3.5, 6 - .5);
    point_set2D(&wheel_centers[1], 6.5, 6 - .5);
    matrix_xformPoint(vtm, &wheel_centers[0], &wheel_centers[0]);
    matrix_xformPoint(vtm, &wheel_centers[1], &wheel_centers[1]);

    Point wheel_radius;
    point_set2D(&wheel_radius, 3, 6);
    matrix_xformPoint(vtm, &wheel_radius, &wheel_radius);
    double r = fabs(wheel_radius.val[0] - wheel_centers[0].val[0]);
    
    Circle wheels[2];
    circle_set(&wheels[0], wheel_centers[0], r);
    circle_set(&wheels[1], wheel_centers[1], r);

    circle_draw(&wheels[0], src, White);
    circle_draw(&wheels[1], src, White);
}

static void draw_ground(Image *src, Matrix *vtm)
{
    Line ground;
    line_set2D(&ground, -world_size, 5, world_size, 5);
    matrix_xformLine(vtm, &ground);
    line_draw(&ground, src, White);
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

static void draw_alienship(Image *src, Matrix *vtm)
{
    Point window_center;
    point_set2D(&window_center, 16, 16);
    matrix_xformPoint(vtm, &window_center, &window_center);

    Point elipse_dx;
    point_set2D(&elipse_dx, 13.5, 15);
    matrix_xformPoint(vtm, &elipse_dx, &elipse_dx);

    Point elipse_dy;
    point_set2D(&elipse_dy, 16, 13.25);
    matrix_xformPoint(vtm, &elipse_dy, &elipse_dy);

    Elipse window;
    elipse_set(
        &window,
        window_center,
        fabs(window_center.val[0] - elipse_dx.val[0]),
        fabs(window_center.val[1] - elipse_dy.val[1]),
        0);
    elipse_draw(&window, src, White);
    
    Point body_top_points[4];
    point_set2D(&body_top_points[0], 12, 15);
    point_set2D(&body_top_points[1], 13, 16);
    point_set2D(&body_top_points[2], 19, 16);
    point_set2D(&body_top_points[3], 20, 15);

    Polygon *body_top_pgon;
    body_top_pgon = polygon_createp(4, body_top_points);
    matrix_xformPolygon(vtm, body_top_pgon);
    polygon_draw(body_top_pgon, src, White);
    polygon_free(body_top_pgon);

    Point body_bot_points[4];
    point_set2D(&body_bot_points[0], 12, 15);
    point_set2D(&body_bot_points[1], 14, 13);
    point_set2D(&body_bot_points[2], 18, 13);
    point_set2D(&body_bot_points[3], 20, 15);

    Polygon *body_bot_pgon;
    body_bot_pgon = polygon_createp(4, body_bot_points);
    matrix_xformPolygon(vtm, body_bot_pgon);
    polygon_draw(body_bot_pgon, src, White);
    polygon_free(body_bot_pgon);

    Point beam_points[4];
    point_set2D(&beam_points[0], 15, 13);
    point_set2D(&beam_points[1], 12, 5);
    point_set2D(&beam_points[2], 20, 5);
    point_set2D(&beam_points[3], 17, 13);
    
    Polygon *beam_pgon;
    beam_pgon = polygon_createp(4, beam_points);
    matrix_xformPolygon(vtm, beam_pgon);
    polygon_draw(beam_pgon, src, White);
    polygon_free(beam_pgon);
}

static void draw_person(Image *src, Matrix *vtm)
{
    Point head_center;
    point_set2D(&head_center, 16, 9);
    Point head_radius;
    point_set2D(&head_radius, 15.5, 9);
    
    matrix_xformPoint(vtm, &head_center, &head_center);
    matrix_xformPoint(vtm, &head_radius, &head_radius);

    double r = fabs(head_radius.val[0] - head_center.val[0]);

    Circle head;
    circle_set(&head, head_center, r);
    circle_draw(&head, src, White);

    Line neck;
    line_set2D(&neck, 16, 8.5, 15.95, 8.05);
    matrix_xformLine(vtm, &neck);
    line_draw(&neck, src, White);

    Line torso;
    line_set2D(&torso, 15.95, 8.05, 16.5, 7);
    matrix_xformLine(vtm, &torso);
    line_draw(&torso, src, White);

    Line rightleg;
    line_set2D(&rightleg, 16.5, 7, 16.6, 5.75);
    matrix_xformLine(vtm, &rightleg);
    line_draw(&rightleg, src, White);

    Line leftleg;
    line_set2D(&leftleg, 16.5, 7, 17.75, 6.9);
    matrix_xformLine(vtm, &leftleg);
    line_draw(&leftleg, src, White);

    Line rightshoulder;
    line_set2D(&rightshoulder, 15.95, 8.05, 16.35, 8.15);
    matrix_xformLine(vtm, &rightshoulder);
    line_draw(&rightshoulder, src, White);

    Line leftshoulder;
    line_set2D(&leftshoulder, 15.95, 8.05, 15.6, 7.95);
    matrix_xformLine(vtm, &leftshoulder);
    line_draw(&leftshoulder, src, White);

    Line rightarm;
    line_set2D(&rightarm, 16.35, 8.15, 17.15, 8);
    matrix_xformLine(vtm, &rightarm);
    line_draw(&rightarm, src, White);

    Line leftarm;
    line_set2D(&leftarm, 15.6, 7.95, 15.25, 7.25);
    matrix_xformLine(vtm, &leftarm);
    line_draw(&leftarm, src, White);
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
    view.dx = 50.0;

    Point vrp;
    point_set2D(&vrp, 12.0, 10.0);
    point_copy(&view.vrp, &vrp);

    Vector x_axis;
    vector_set(&x_axis, 1.0, 0.0, 0.0);
    vector_copy(&view.x, &x_axis);

    Matrix vtm;
    matrix_setView2D(&vtm, &view);

    draw_grid(src, &vtm);
    draw_ground(src, &vtm);
    draw_car(src, &vtm);
    draw_alienship(src, &vtm);
    draw_person(src, &vtm);

    image_write(src, "output/lab5/view2D.ppm");
}
