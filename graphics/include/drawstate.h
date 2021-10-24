/**
 * Greg Attra
 * 10/23/2021
 * 
 * Header file defining the DrawState struct and API.
 */

#include "image.h"
#include "point.h"

typedef enum
{
    ShadeFrame,
    ShadeConstant,
    ShadeDepth,
    ShadeFlat,
    ShadeGouraud,
    ShadePhong
} ShadeMethod;

typedef struct
{
    Color color;
    Color flatColor;
    Color body;
    Color surface;
    float surfaceCoeff;
    ShadeMethod shade;
    int zBuffer;
    Point viewer;
} DrawState;

/**
 * Create new draw state object and initialize fields.
 * 
 * @return pointer to initialized draw state
 */
DrawState *drawstate_create(void);

/**
 * Set the draw state color field.
 * 
 * @param ds the draw state to update
 * @param c the color to set
 * 
 * @return void
 */
void drawstate_setColor(DrawState *ds, Color c);

/**
 * Set the draw state flat color field.
 * 
 * @param ds the draw state to update
 * @param c the color to set
 * 
 * @return void
 */
void drawstate_setFlatColor(DrawState *ds, Color c);

/**
 * Set the draw state body field.
 * 
 * @param ds the draw state to update
 * @param c the color value to set
 * 
 * @return void
 */
void drawstate_setBody(DrawState *ds, Color c);

/**
 * Set the draw state surface color.
 * 
 * @param ds the draw state to update
 * @param c the color value to set
 * 
 * @return void
 */
void drawstate_setSurface(DrawState *ds, Color c);

/**
 * Set the draw state coeff field.
 * 
 * @param ds the draw state to update
 * @param sc the surface coeff value to set
 * 
 * @return void
 */
void drawstate_setSurfaceCoeff(DrawState *ds, float sc);

/**
 * Copy one draw state to another.
 * 
 * @param to the target draw state
 * @param from the source draw state
 * 
 * @return void
 */
void drawstate_copy(DrawState *to, DrawState *from);

/**
 * Free the draw state struct.
 * 
 * @param ds the draw state to free
 * 
 * @return void
 */
void drawstate_free(DrawState *ds);

/**
 * Set the shade method on the draw state.
 * 
 * @param ds the draw state to update
 * @param sm the shade method to set
 * 
 * @return void
 */
void void drawstate_setShade(DrawState *ds, ShadeMethod sm);
