/**
 * Greg Attra
 * 09/23/2021
 * 
 * Definition of the image API.
 */

#ifndef IMAGE_H
#define IMAGE_H

/**
 * Structure representing a pixel in an image.
 */
typedef struct {
    float rgb[3];
    float a;
    float z;
} FPixel;

/**
 * Structure representing an image.
 */
typedef struct {
    int rows;
    int cols;
    FPixel *data;
} Image;

/**
 * Structure representing color.
 */
typedef struct {
    float c[3];
} Color;

/**
 * Create an image in memory.
 * 
 * @param rows the number of pixel rows
 * @param cols the number of pixel cols
 * 
 * @return a pointer to an Image struct
 */
Image* image_create(int rows, int cols);

/**
 * Given uninitialized Image, set values to default.
 * 
 * @param src the source image
 * 
 * @return void
 */
void image_init(Image *src);

/**
 * Write an image to a file.
 * 
 * @param src the image to write
 * @param filename the name of the file to write out
 *
 * @return 0 for success, 1 for fail
 */
int image_write(Image *src, char *filename);

/**
 * Reads an image from the given file.
 * 
 * @param filename the name of the image file to read
 * 
 * @return a populated image struct
 */
Image* image_read(char *filename);

/**
 * Deallocates image data and frees the Image struct.
 * 
 * @param src the image to free
 * 
 * @return void
 */
void image_free(Image *src);

/**
 * Allocates space for the data given the rows and cols and sets their values
 * to the defaults.
 * 
 * @param src the image to allocate
 * @param rows the rows of the image
 * @param cols the cols of the image
 * 
 * @return 0 for success, 1 failure
 */
int image_alloc(Image *src, int rows, int col);

/**
 * Deallocates existing image data and resets to default.
 *
 * @param src the source image
 * 
 * @return void
 */
void image_dealloc(Image *src);

/**
 * Returns the pixel at (r, c).
 * 
 * @param src the image to search
 * @param i the row
 * @param j the column
 * 
 * @return the pixel at (r,c)
 */
FPixel image_getf(Image *src, int i, int j);

/**
 * Returns the value of channel c at (i, j).
 * 
 * @param src the source image to search
 * @param i the row
 * @param j the column
 * @param c the channel
 * 
 * @return the channel value
 */
float image_getc(Image *src, int i, int j, int c);

/**
 * Gets the alpha value of the pixel at (i, j).
 * 
 * @param src the source image to search
 * @param i the row
 * @param j the column
 * 
 * @return the alpha value of the pixel
 */
float image_geta(Image *src, int i, int j);

/**
 * Gets the z value of the pixel at (i, j).
 * 
 * @param src the source image to search
 * @param i the row
 * @param j the column
 * 
 * @return the z value of the pixel
 */
float image_getz(Image *src, int i, int j);

/**
 * Set the pixel value for the specified (i, j) in the source image.
 * 
 * @param src the source image
 * @param i the pixel row
 * @param j the pixel col
 * @param val the pixel to set
 * 
 * @return void
 */
void image_setf(Image *src, int i, int j, FPixel val);

/**
 * Set the channel value for the specified pixel in the source image.
 * 
 * @param src the source image
 * @param i the pixel row
 * @param j the pixel col
 * @param c the pixel channel to set
 * @param value the value of the channel
 * 
 * @return void
 */
void image_setc(Image *src, int i, int j, int c, float value);

/**
 * Set the alpha value for the pixel at (i, j) in the source image.
 * 
 * @param src the source image
 * @param i the pixel row
 * @param j the pixel col
 * @param val the alpha value to set
 * 
 * @return void
 */
void image_seta(Image *src, int i, int j, float val);

/**
 * Set the z value for the specified (i, j) in the source image.
 * 
 * @param src the source image
 * @param i the pixel row
 * @param j the pixel col
 * @param val the z value to set
 * 
 * @return void
 */
void image_setz(Image *src, int i, int j, float val);

/**
 * Resets every pixel to a default.
 * 
 * @param src the source image
 * 
 * @return void
 */
void image_reset(Image *src);

/**
 * Fills the image given the target pixel val.
 * 
 * @param src the source image
 * @param val the pixel val
 * 
 * @return void
 */
void image_fill(Image *src, FPixel val);

/**
 * Sets the rgb of each pixel to the specified rgb values.
 * 
 * @param src the source image to set
 * @param r the red val
 * @param g the green val
 * @param b the blue val
 * 
 * @return void
 */
void image_fillrgb(Image *src, float r, float g, float b);

/**
 * Sets the alpha for each pixel.
 * 
 * @param src the source image
 * @param a the alpha to set
 * 
 * @return void
 */
void image_filla(Image *src, float a);

/**
 * Sets the z value for each pixel in the image.
 * 
 * @param src the source image
 * @param z the z value
 * 
 * @return void
 */
void image_fillz(Image *src, float z);

/**
 * Copies one color to another.
 * 
 * @param to the target color
 * @param from the source color
 * 
 * @return void
 */
void color_copy(Color *to, Color *from);

/**
 * Set the color values given the rgb.
 * 
 * @param to the target color
 * @param r the red val
 * @param g the green val
 * @param b the blue val
 * 
 * @return void
 */
void color_set(Color *to, float r, float g, float b);

/**
 * Sets the color value of the pixel at (i, j).
 * 
 * @param src the source image
 * @param i the row
 * @param j the column
 * @param val the color to set
 * 
 * @return void
 */
void image_setColor(Image *src, int i, int j, Color val);

/**
 * Get the color at (i, j).
 * 
 * @param src the source image
 * @param i the row
 * @param j the col
 * 
 * @return the color of the pixel
 */
Color image_getColor(Image *src, int i, int j);

/**
 * Compoare two colors to see if they match.
 * 
 * @param one first color
 * @param two second color
 * 
 * @return 0 if match, 1 otherwise
 */
int color_compare(Color *one, Color *two);

#endif