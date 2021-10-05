/**
 * Greg Attra
 * 10/04/2021
 * 
 * Program to draw a bike.
 */

#include "image.h"
#include "circle.h"
#include "polyline.h"
#include "line.h"
#include "point.h"
#include "elipse.h"
#include <math.h>
#include <stdlib.h>

#define WHEEL_RADIUS 50.0
#define REAR_WHEEL_X 150
#define REAR_WHEEL_Y 200
#define BASE_WIDTH 75.0
#define IMG_HEIGHT 300
#define IMG_WIDTH 500

Color BLACK = {0.0, 0.0, 0.0};
Color BLUE = {0.0, 0.0, 1.0};
Color GREEN = {0.0, 1.0, 0.0};

static void draw_spoke(int x, int y, int r, float a, Image *src, Color col)
{
    Line spoke;
    line_set2D(
        &spoke,
        x + r * sin(a * (M_PI / 3)),
        y + r * cos(a * (M_PI / 3)),
        x + r * sin(M_PI + a * (M_PI / 3)),
        y + r * cos(M_PI + a * (M_PI / 3)));
    line_draw(&spoke, src, col);
}

static void draw_spokes(Circle wheel, Image *src, Color col)
{
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 1.0, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 1.5, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 2.0, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 2.5, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 3.0, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 3.5, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 4.0, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 4.5, src, BLACK);
   draw_spoke(wheel.center.val[0], wheel.center.val[1], wheel.radius, 5.0, src, BLACK);
}

int main(int argc, char *argv[])
{
    Image *src;
    src = image_create(IMG_HEIGHT, IMG_WIDTH);
    image_fillrgb(src, 214.0/255.0, 203.0/255.0, 171.0/255.0);

    Circle rear_wheel;
    Point rear_wheel_center;
    point_set2D(&rear_wheel_center, REAR_WHEEL_X, REAR_WHEEL_Y);
    circle_set(&rear_wheel, rear_wheel_center, WHEEL_RADIUS);
    circle_draw(&rear_wheel, src, BLACK);
    circle_set(&rear_wheel, rear_wheel.center, rear_wheel.radius + 1);
    circle_draw(&rear_wheel, src, BLACK);
    circle_set(&rear_wheel, rear_wheel.center, rear_wheel.radius + 2);
    circle_draw(&rear_wheel, src, BLACK);

    Circle front_wheel;
    Point front_wheel_center;
    point_set2D(&front_wheel_center, REAR_WHEEL_X + BASE_WIDTH + 2*WHEEL_RADIUS, REAR_WHEEL_Y);
    circle_set(&front_wheel, front_wheel_center, WHEEL_RADIUS);
    circle_draw(&front_wheel, src, BLACK);
    circle_set(&front_wheel, front_wheel.center, front_wheel.radius + 1);
    circle_draw(&front_wheel, src, BLACK);
    circle_set(&front_wheel, front_wheel.center, front_wheel.radius + 2);
    circle_draw(&front_wheel, src, BLACK);

    Point base_start;
    point_set2D(
            &base_start,
            rear_wheel.center.val[0],
            rear_wheel.center.val[1]);
    Point base_end;
    point_set2D(
            &base_end,
            rear_wheel.center.val[0] + BASE_WIDTH + WHEEL_RADIUS / 2,
            rear_wheel.center.val[1]);
    Point backbone_start;
    point_set2D(
            &backbone_start,
            base_end.val[0] + 50.0,
            base_end.val[1] - 75.0);
    Point backbone_end;
    point_set2D(
            &backbone_end,
            rear_wheel.center.val[0] + 50.0,
            backbone_start.val[1]);
    Point base_incline;
    point_set2D(
            &base_incline,
            backbone_start.val[0],
            backbone_start.val[1]);
    Point front_brace;
    point_set2D(
            &front_brace,
            front_wheel.center.val[0],
            front_wheel.center.val[1]);

    Point vlist[6] = { backbone_start, backbone_end, base_start, base_end, base_incline, front_brace };

    Polyline *pline = polyline_createp(6, vlist);
    polyline_draw(pline, src, BLUE);
    polyline_free(pline);

    Line cross_brace;
    line_set2D(
        &cross_brace,
        backbone_end.val[0],
        backbone_end.val[1],
        base_end.val[0],
        base_end.val[1]);
    line_draw(&cross_brace, src, BLUE);

    Line seat_lift;
    line_set2D(
            &seat_lift,
            backbone_end.val[0],
            backbone_end.val[1],
            backbone_end.val[0] - 5.0,
            backbone_end.val[1] - 20.0);
    line_draw(&seat_lift, src, BLUE);

    Line handlebar_brace;
    line_set2D(
            &handlebar_brace,
            backbone_start.val[0],
            backbone_start.val[1],
            backbone_start.val[0],
            backbone_start.val[1] - 20.0);
    line_draw(&handlebar_brace, src, BLUE);

    Line handlebar;
    line_set2D(
            &handlebar,
            handlebar_brace.b.val[0] - 10.0,
            handlebar_brace.b.val[1] - 5.0,
            handlebar_brace.b.val[0] + 10.0,
            handlebar_brace.b.val[1] + 5.0);
    line_draw(&handlebar, src, BLACK);

    Line peddal_connector;
    line_set2D(
        &peddal_connector,
        base_end.val[0],
        base_end.val[1],
        base_end.val[0] + 10.0,
        base_end.val[1] + 25.0);
    line_draw(&peddal_connector, src, BLUE);

    Line peddal_1;
    line_set2D(
        &peddal_1,
        peddal_connector.b.val[0] - 5.0,
        peddal_connector.b.val[1],
        peddal_connector.b.val[0] + 5.0,
        peddal_connector.b.val[1]);
    Line peddal_2;
    line_set2D(
        &peddal_2,
        peddal_connector.b.val[0] - 5.0,
        peddal_connector.b.val[1] - 1,
        peddal_connector.b.val[0] + 5.0,
        peddal_connector.b.val[1] - 1);
    Line peddal_3;
    line_set2D(
        &peddal_3,
        peddal_connector.b.val[0] - 5.0,
        peddal_connector.b.val[1] - 2,
        peddal_connector.b.val[0] + 5.0,
        peddal_connector.b.val[1] - 2);
    line_draw(&peddal_1, src, BLACK);
    line_draw(&peddal_2, src, BLACK);
    line_draw(&peddal_3, src, BLACK);

    Elipse seat;
    elipse_set(
            &seat,
            seat_lift.b,
            20.0,
            5.0,
            0.0);
    elipse_drawFill(&seat, src, BLACK);

    Circle front_wheel_cap;
    circle_set(
        &front_wheel_cap,
        front_wheel_center,
        7.5);
    Circle rear_wheel_cap;
    circle_set(
        &rear_wheel_cap,
        rear_wheel_center,
        7.5);
    circle_drawFill(&front_wheel_cap, src, BLACK);
    circle_drawFill(&rear_wheel_cap, src, BLACK);

    Circle main_gear;
    circle_set(
        &main_gear,
        base_end,
        15.0);
    circle_draw(&main_gear, src, BLACK);

    Line top_chain;
    line_set2D(
        &top_chain,
        rear_wheel_cap.center.val[0],
        rear_wheel_cap.center.val[1] + rear_wheel_cap.radius,
        main_gear.center.val[0],
        main_gear.center.val[1] + main_gear.radius);
    Line bottom_chain;
    line_set2D(
        &bottom_chain,
        rear_wheel_cap.center.val[0],
        rear_wheel_cap.center.val[1] - rear_wheel_cap.radius,
        main_gear.center.val[0],
        main_gear.center.val[1] - main_gear.radius);
    line_draw(&top_chain, src, BLACK);
    line_draw(&bottom_chain, src, BLACK);

    Circle gear_base;
    circle_set(
        &gear_base,
        main_gear.center,
        2.5);
    circle_drawFill(&gear_base, src, BLACK);

    draw_spokes(rear_wheel, src, BLACK);
    draw_spokes(front_wheel, src, BLACK);

    image_write(src, "output/lab3/illustration.ppm");

    image_free(src);
}
