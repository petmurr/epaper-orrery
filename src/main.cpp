#include <iostream>
#include <stdint.h>
#include "epsim.h"
#include "ws.h"

int main() {
    std::cout << "---- epaper-orrery ----" << std::endl;

    Epsim e(400, 300); 
    Ws ws;

    // manually create image for now
    uint8_t *image;
    ws.Paint.Image = nullptr; 
    ws.Paint.WidthMemory = 400;
    ws.Paint.HeightMemory = 300;
    ws.Paint.Color = 0xFF; // white    
    ws.Paint.Scale = 2;
    ws.Paint.WidthByte = (400 % 8 == 0)? (400 / 8 ): (400 / 8 + 1);
    ws.Paint.HeightByte = 300;    

    ws.Paint_DrawCircle(150, 150, 100, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    e.Image2Vector(ws.Paint.Image, sizeof(ws.Paint.Image));

    e.Save("image.png");

    return 0;
}