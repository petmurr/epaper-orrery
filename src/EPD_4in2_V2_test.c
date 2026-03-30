#include "EPD_Test.h"
#include "EPD_4in2_V2.h"
#include <string.h>
#include "math.h"

typedef struct 
{
    int x;
    int y;
} vec2;

void DumpBufferPBM(const char *name, UBYTE *buf) {
    printf("P4\n%d %d\n", EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT);

    int row_bytes = (EPD_4IN2_V2_WIDTH + 7) / 8;
    for (int y = 0; y < EPD_4IN2_V2_HEIGHT; y++) {
        fwrite(&buf[y * row_bytes], 1, row_bytes, stdout);
    }
}

// int before()
// {
    // UBYTE *BlackImage;
    // /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    // UWORD Imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0)? (EPD_4IN2_V2_WIDTH / 8 ): (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;
    // if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    //     printf("Failed to apply for black memory...\r\n");
    //     return -1;
    // }
    // printf("Paint_NewImage\r\n");
    // Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    // Paint_SelectImage(BlackImage);
    // Paint_Clear(WHITE);

    // for (int i = 0; i < 8; ++i)
    // {
    //     // Draw orbit line
    //     int orbital_radius_px = (distance_mod[i]*planet_distance[i])*NEPTUNE_ORBITAL_RADIUS_IN_PIXELS;
    //     Paint_DrawCircle(200 + offset.x, 150 + offset.y, orbital_radius_px, darkmode ? WHITE : BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY); 

    //     // Draw planet & outline
    //     int planet_radius_px = (radius_mod[i]*planet_radius[i])*JUPITER_RADIUS_IN_PIXELS;
    //     int outline_radius_px = planet_radius_px + i;
        
    //     // Find x, y coords on canvas corresponding to planet's distance
    //     // vec2 pos = deg2coords(planetAngle(orbital_periods[i])+initial_angles[i], orbital_radius_px);
    //     // vec2 pos = deg2coords(planetAngle2(i), orbital_radius_px);
    //     vec2 pos = deg2coords(planetAngle2(i), orbital_radius_px, offset);

    //     Paint_DrawCircle(pos.x, pos.y, outline_radius_px, darkmode ? BLACK : WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    //     Paint_DrawCircle(pos.x, pos.y, planet_radius_px, darkmode ? WHITE : BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    // }

    // // 2.Drawing on the image
    // printf("Drawing:BlackImage\r\n");

    // EPD_4IN2_V2_Display(BlackImage);
	// DEV_Delay_ms(2000);
    
// }

// 0 if work
// else if not
int after()
{
    
}

int EPD_4in2_V2_test(void)
{
    printf("test\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }
    printf("clearing...\r\n");
    EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    DEV_Delay_ms(500);

    // =================================================================== start

    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0)? (EPD_4IN2_V2_WIDTH / 8 ): (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }

    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    //
    Paint_Clear(BLACK);
    Paint_DrawCircle(131, 221, 11, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(125, 230, 2, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(125, 230, 2, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(131, 221, 21, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(143, 203, 4, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(143, 203, 4, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(131, 221, 29, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(102, 225, 6, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(102, 225, 6, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(131, 221, 44, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(172, 235, 5, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(172, 235, 5, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(131, 221, 91, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(87, 140, 17, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(87, 140, 17, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(131, 221, 139, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(269, 208, 16, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(269, 208, 16, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(131, 221, 188, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(229, 60, 10, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(229, 60, 10, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(131, 221, 233, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(363, 213, 11, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(363, 213, 11, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    //
    // 2.Drawing on the image
    printf("Drawing:BlackImage\r\n");

    EPD_4IN2_V2_Display(BlackImage);
	DEV_Delay_ms(2000);
    
    // =================================================================== end

    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    return 0;
}






