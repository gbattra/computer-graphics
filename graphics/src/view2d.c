/**
 * Greg Attra
 * 10/18/2021
 * 
 * Executable for generating a gif in 2D where the view zooms and pans.
 */

#include "graphics.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Color White = {1.0, 1.0, 1.0};
Color Gray = {0.25, 0.25, 0.25};
Color Red = {1.0, 0.0, 0.0};

int world_size = 100;
double horizon = 5.0;

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
    
    Circle wheels[2];
    circle_set(&wheels[0], wheel_centers[0], .5);
    circle_set(&wheels[1], wheel_centers[1], .5);

    matrix_xformCircle(vtm, &wheels[0]);
    matrix_xformCircle(vtm, &wheels[1]);

    circle_draw(&wheels[0], src, White);
    circle_draw(&wheels[1], src, White);
}

static void draw_ground(Image *src, Matrix *vtm)
{
    Line ground;
    line_set2D(&ground, -world_size, horizon, world_size, horizon);
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

    Circle center;
    circle_set(&center, c, .25);
    matrix_xformCircle(vtm, &center);
    circle_drawFill(&center, src, Red);
}

static void draw_alienship(Image *src, Matrix *vtm)
{
    Point window_center;
    point_set2D(&window_center, 16, 16);

    Elipse window;
    elipse_set(
        &window,
        window_center,
        2.5,
        2.75,
        0);
    matrix_xformElipse(vtm, &window);
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

    Circle head;
    circle_set(&head, head_center, 0.5);
    matrix_xformCircle(vtm, &head);
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

static void draw_house(Image *src, Matrix *vtm)
{
    Point housebody_points[4];
    point_set2D(&housebody_points[0], 26, horizon);
    point_set2D(&housebody_points[1], 26, 12);
    point_set2D(&housebody_points[2], 38, 12);
    point_set2D(&housebody_points[3], 38, horizon);

    Polygon *housebody_pgon;
    housebody_pgon = polygon_createp(4, housebody_points);
    matrix_xformPolygon(vtm, housebody_pgon);
    polygon_draw(housebody_pgon, src, White);
    polygon_free(housebody_pgon);

    Point roof_points[3];
    point_set2D(&roof_points[0], 26, 12);
    point_set2D(&roof_points[1], 32, 17);
    point_set2D(&roof_points[2], 38, 12);

    Polygon *roof_pgon;
    roof_pgon = polygon_createp(3, roof_points);
    matrix_xformPolygon(vtm, roof_pgon);
    polygon_draw(roof_pgon, src, White);
    polygon_free(roof_pgon);

    Point window_points[4];
    point_set2D(&window_points[0], 29, 6.5);
    point_set2D(&window_points[1], 29, 10.5);
    point_set2D(&window_points[2], 35, 10.5);
    point_set2D(&window_points[3], 35, 6.5);

    Polygon *window_pgon;
    window_pgon = polygon_createp(4, window_points);
    matrix_xformPolygon(vtm, window_pgon);
    polygon_draw(window_pgon, src, White);
    polygon_free(window_pgon);

    Point door_points[4];
    point_set2D(&door_points[0], 26, 9);
    point_set2D(&door_points[1], 24, 9);
    point_set2D(&door_points[2], 24, horizon);
    point_set2D(&door_points[3], 26, horizon);

    Polygon *door_pgon;
    door_pgon = polygon_createp(4, door_points);
    matrix_xformPolygon(vtm, door_pgon);
    polygon_draw(door_pgon, src, White);
    polygon_free(door_pgon);

    Point doorknob_center;
    point_set2D(&doorknob_center, 24.5, 6.5);
    Circle doorknob;
    circle_set(&doorknob, doorknob_center, .15);
    matrix_xformCircle(vtm, &doorknob);
    circle_draw(&doorknob, src, White);

}

int main(int argc, char* argv[])
{
    char filename[256];
    int nframes = 20;
    int rows = 900;
    int cols = 1200;
    Image *src;
    src = image_create(rows, cols);

    double dx = 15.0;
    Point vrp;
    point_set2D(&vrp, 2.0, 10.0);
    Vector x_axis;
    vector_set(&x_axis, 1.0, 0.0, 0.0);

    double pan_step = 1;
    double zoom_step = 2;
    
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

        draw_grid(src, &vtm);
        draw_ground(src, &vtm);
        draw_car(src, &vtm);
        draw_alienship(src, &vtm);
        draw_person(src, &vtm);
        draw_house(src, &vtm);

        sprintf(filename, "output/lab5/scene2D/frame-%04d.ppm", i);
        image_write(src, filename);

        dx += zoom_step;
        point_set2D(&vrp, vrp.val[0] + pan_step, vrp.val[1]);
    }
}
