/**
 * Greg Attra
 * 09/27/2021
 * 
 * Header for the Julia set functions
 */

#ifndef FRACTALS
#define FRACTALS

#include "image.h"

/**
 * Generates a Julia set image.
 * 
 * @param dst the dest image
 * @param x0 start x
 * @param y0 start y
 * @param dx constant for x
 *
 * @return void
 */
void julia(Image *dst, float x0, float y0, float dx);

/**
 * Generates a Mandelbrot set image.
 * 
 * @param dst the dest image
 * @param x0 the start x
 * @param y0 the start y
 * @param dx constant for x
 * 
 * @return void
 */
void mandelbrot( Image *dst, float x0, float y0, float dx);

#endif
