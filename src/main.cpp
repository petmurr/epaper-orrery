#include <iostream>
#include <stdint.h>
#include "epsim.h"
#include "ws.h"

#define EPD_4IN2_V2_WIDTH 400
#define EPD_4IN2_V2_HEIGHT 300

int main() {
    std::cout << "---- epaper-orrery ----" << std::endl;

    Epsim e(400, 300); 
    Ws ws;

    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0)? (EPD_4IN2_V2_WIDTH / 8 ): (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }

    ws.Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    ws.Paint_SelectImage(BlackImage);
    ws.Paint_Clear(WHITE);

    ws.Paint_DrawCircle(150, 150, 100, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    e.Image2Vector(ws.Paint.Image, Imagesize);

    e.Save("image.png");

    return 0;
}