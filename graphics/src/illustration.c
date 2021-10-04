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
#include <stdlib.h>

#define WHEEL_RADIUS 50.0
#define REAR_WHEEL_X 300
#define REAR_WHEEL_Y 400
#define BASE_WIDTH 75.0

Color BLACK = {0.0, 0.0, 0.0};
Color BLUE = {0.0, 0.0, 1.0};

static void draw_spokes(Circle *circ, Image *src, Color col)
{

}

int main(int argc, char *argv[])
{
    Image *src;
    src = image_create(600, 900);
    image_fillrgb(src, 1.0, 1.0, 1.0);

    Circle rear_wheel;
    Point rear_wheel_center;
    point_set2D(&rear_wheel_center, REAR_WHEEL_X, REAR_WHEEL_Y);
    circle_set(&rear_wheel, rear_wheel_center, WHEEL_RADIUS);
    circle_draw(&rear_wheel, src, BLACK);

    Circle front_wheel;
    Point front_wheel_center;
    point_set2D(&front_wheel_center, REAR_WHEEL_X + BASE_WIDTH + 2*WHEEL_RADIUS, REAR_WHEEL_Y);
    circle_set(&front_wheel, front_wheel_center, WHEEL_RADIUS);
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

    Elipse seat;
    elipse_set(
            &seat,
            seat_lift.b,
            20.0,
            5.0,
            0.0);
    elipse_drawFill(&seat, src, BLACK);

    image_write(src, "output/lab3/illustration.ppm");

    image_free(src);
}
