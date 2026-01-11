#pragma once

#include <stdint.h>

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

typedef enum {
    DOT_PIXEL_1X1  = 1,		// 1 x 1
    DOT_PIXEL_2X2  , 		// 2 X 2
    DOT_PIXEL_3X3  ,		// 3 X 3
    DOT_PIXEL_4X4  ,		// 4 X 4
    DOT_PIXEL_5X5  , 		// 5 X 5
    DOT_PIXEL_6X6  , 		// 6 X 6
    DOT_PIXEL_7X7  , 		// 7 X 7
    DOT_PIXEL_8X8  , 		// 8 X 8
} DOT_PIXEL;
#define DOT_PIXEL_DFT  DOT_PIXEL_1X1  //Default dot pilex

typedef struct {
    UBYTE *Image;
    UWORD Width;
    UWORD Height;
    UWORD WidthMemory;
    UWORD HeightMemory;
    UWORD Color;
    UWORD Rotate;
    UWORD Mirror;
    UWORD WidthByte;
    UWORD HeightByte;
    UWORD Scale;
} PAINT;

typedef enum {
    DRAW_FILL_EMPTY = 0,
    DRAW_FILL_FULL,
} DRAW_FILL;

typedef enum {
    DOT_FILL_AROUND  = 1,		// dot pixel 1 x 1
    DOT_FILL_RIGHTUP  , 		// dot pixel 2 X 2
} DOT_STYLE;
#define DOT_STYLE_DFT  DOT_FILL_AROUND  //Default dot pilex

typedef enum {
    MIRROR_NONE  = 0x00,
    MIRROR_HORIZONTAL = 0x01,
    MIRROR_VERTICAL = 0x02,
    MIRROR_ORIGIN = 0x03,
} MIRROR_IMAGE;
#define MIRROR_IMAGE_DFT MIRROR_NONE

#define ROTATE_0            0
#define ROTATE_90           90
#define ROTATE_180          180
#define ROTATE_270          270

#define WHITE          0xFF
#define BLACK          0x00
#define RED            BLACK

class Ws
{    
public:
    PAINT Paint;

    bool debug = true;

    Ws();

    void Paint_DrawCircle(  UWORD X_Center, UWORD Y_Center, UWORD Radius,
                            UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill);
              
    void Paint_DrawPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color,
                        DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_Style);
    
    void Paint_SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color);
    void Debug(std::string str);
    void Paint_Clear(UWORD Color);
    void Paint_NewImage(UBYTE *image, UWORD Width, UWORD Height, UWORD Rotate, UWORD Color);
    void Paint_SelectImage(UBYTE *image);
};