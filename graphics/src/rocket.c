/**
 * Greg Attra
 * 10/10/2021
 * 
 * Image of a rocket for Lab 4 part 4.
 */

#include "graphics.h"
#include <math.h>

int main(int argc, char *argv[])
{
    Color white = {1.0, 1.0, 1.0};
    Color gray = {0.85, 0.85, 0.85};
    Color black = {21.0/255.0, 28.0/255.0, 33.0/255.0};
    Image *src;
    src = image_create(900, 500);
    
    // draw bg
    Color skyblue;
    color_set(&skyblue, 11.0/255.0, 55.0/255.0, 66.0/255.0);
    for (int r = 0; r < src->rows; r++)
    {
        Line l;
        line_set2D(&l, 0, r, src->cols, r);
        line_draw(&l, src, skyblue);

        color_set(&skyblue, skyblue.c[0] + 0.0005, skyblue.c[1] + 0.0005, skyblue.c[2] + 0.0005);
    }

    // draw stars
    double thresh = 0.3;
    for (int s = 0; s < src->rows; s++)
    {
        float random = (float) rand() / (float) RAND_MAX;
        while (random >= thresh)
        {
            float xrand = (float) rand() / (float) RAND_MAX;
            int x = (int) (xrand * (float) src->cols);
            image_setColor(src, s, x, white);

            random = (float) rand() / (float) RAND_MAX;
        }
        thresh += 0.001;
    }

    // draw exhaust
    Circle circles[15];
    Point p[15];
    point_set2D(&p[0], (src->cols / 2), 455);
    circle_set(&circles[0], p[0], 10.0);
    point_set2D(&p[1], (src->cols / 2), 475);
    circle_set(&circles[1], p[1], 15.0);
    point_set2D(&p[2], (src->cols / 2), 515);
    circle_set(&circles[2], p[2], 30.0);
    point_set2D(&p[3], (src->cols / 2), 585);
    circle_set(&circles[3], p[3], 60.0);
    point_set2D(&p[4], (src->cols / 2), 660);
    circle_set(&circles[4], p[4], 90.0);
    point_set2D(&p[5], (src->cols / 2), 800);
    circle_set(&circles[5], p[5], 160.0);
    point_set2D(&p[6], (src->cols / 2), 1030);
    circle_set(&circles[6], p[6], 300.0);

    Color colors[7];
    color_set(&colors[0], 247.0/255.0, 92.0/255.0, 92.0/255.0);
    color_set(&colors[1], 247.0/255.0, 122.0/255.0, 122.0/255.0);
    color_set(&colors[2], 247.0/255.0, 155.0/255.0, 142.0/255.0);
    color_set(&colors[3], 247.0/255.0, 175.0/255.0, 142.0/255.0);
    color_set(&colors[4], 247.0/255.0, 205.0/255.0, 142.0/255.0);
    color_set(&colors[5], 247.0/255.0, 235.0/255.0, 182.0/255.0);
    color_set(&colors[6], 247.0/255.0, 235.0/255.0, 222.0/255.0);
    for (int i = 0; i < 15; i++)
    {
        circle_drawFill(&circles[i], src, colors[i]);
    }
    
    // draw ship
    Point shipbody[5];
    point_set2D(&shipbody[0], src->cols / 2, 50);
    point_set2D(&shipbody[1], (src->cols / 2) + 35, 120);
    point_set2D(&shipbody[2], (src->cols / 2) + 35, 425);
    point_set2D(&shipbody[3], (src->cols / 2) - 35, 425);
    point_set2D(&shipbody[4], (src->cols / 2) - 35, 120);

    Polygon *shipbody_pgon;
    shipbody_pgon = polygon_createp(5, shipbody);
    polygon_drawFillG(shipbody_pgon, src, gray, black, 0);
    polygon_free(shipbody_pgon);

    Point leftwing[4];
    point_set2D(&leftwing[0], (src->cols / 2) - 35, 300);
    point_set2D(&leftwing[1], (src->cols / 2) - 75, 380);
    point_set2D(&leftwing[2], (src->cols / 2) - 85, 410);
    point_set2D(&leftwing[3], (src->cols / 2) - 35, 420);
    
    Polygon *leftwing_pgon;
    leftwing_pgon = polygon_createp(4, leftwing);
    polygon_drawFill(leftwing_pgon, src, black);
    polygon_free(leftwing_pgon);

    Point rightwing[4];
    point_set2D(&rightwing[0], (src->cols / 2) + 35, 300);
    point_set2D(&rightwing[1], (src->cols / 2) + 75, 380);
    point_set2D(&rightwing[2], (src->cols / 2) + 85, 410);
    point_set2D(&rightwing[3], (src->cols / 2) + 35, 420);
    
    Polygon *rightwing_pgon;
    rightwing_pgon = polygon_createp(4, rightwing);
    polygon_drawFill(rightwing_pgon, src, black);
    polygon_free(rightwing_pgon);

    Point booster[4];
    point_set2D(&booster[0], (src->cols / 2) - 35, 425);
    point_set2D(&booster[1], (src->cols / 2) - 15, 445);
    point_set2D(&booster[2], (src->cols / 2) + 15, 445);
    point_set2D(&booster[3], (src->cols / 2) + 35, 425);
    Polygon *booster_pgon;
    booster_pgon = polygon_createp(4, booster);
    polygon_drawFill(booster_pgon, src, black);
    polygon_free(booster_pgon);

    Point upperleft_wing[3];
    point_set2D(&upperleft_wing[0], (src->cols / 2) - 35, 150);
    point_set2D(&upperleft_wing[1], (src->cols / 2) - 65, 250);
    point_set2D(&upperleft_wing[2], (src->cols / 2) - 35, 265);
    Polygon *upperleft_wing_pgon;
    upperleft_wing_pgon = polygon_createp(3, upperleft_wing);
    polygon_drawFill(upperleft_wing_pgon, src, black);
    polygon_free(upperleft_wing_pgon);

    Point upperright_wing[3];
    point_set2D(&upperright_wing[0], (src->cols / 2) + 35, 150);
    point_set2D(&upperright_wing[1], (src->cols / 2) + 65, 250);
    point_set2D(&upperright_wing[2], (src->cols / 2) + 35, 265);
    Polygon *upperright_wing_pgon;
    upperright_wing_pgon = polygon_createp(3, upperright_wing);
    polygon_drawFill(upperright_wing_pgon, src, black);
    polygon_free(upperright_wing_pgon);

    Point botmidwing[4];
    point_set2D(&botmidwing[0], (src->cols / 2), 300);
    point_set2D(&botmidwing[1], (src->cols / 2) + 15, 410);
    point_set2D(&botmidwing[2], (src->cols / 2), 420);
    point_set2D(&botmidwing[3], (src->cols / 2) - 15, 410);
    Polygon *botmidwing_pgon;
    botmidwing_pgon = polygon_createp(4, botmidwing);
    polygon_drawFill(botmidwing_pgon, src, black);
    polygon_free(botmidwing_pgon);

    Point cockpit[6];
    point_set2D(&cockpit[0], (src->cols / 2) + 5, 75);
    point_set2D(&cockpit[1], (src->cols / 2) + 25, 115);
    point_set2D(&cockpit[2], (src->cols / 2) + 20, 120);
    point_set2D(&cockpit[3], (src->cols / 2) - 20, 120);
    point_set2D(&cockpit[4], (src->cols / 2) - 25, 115);
    point_set2D(&cockpit[5], (src->cols / 2) - 5, 75);
    Polygon *cockpit_pgon;
    cockpit_pgon = polygon_createp(6, cockpit);
    polygon_drawFill(cockpit_pgon, src, black);
    polygon_free(cockpit_pgon);

    Circle windows[3];
    int wrow = 175;
    for (int w = 0; w < 3; w++)
    {
        Point p;
        point_set2D(&p, (src->cols / 2), wrow);
        circle_set(&windows[w], p, 10.0);
        circle_drawFill(&windows[w], src, black);
        wrow += 30;
    }

    image_write(src, "output/lab4/rocket.ppm");

    image_free(src);

    return 0;
}
