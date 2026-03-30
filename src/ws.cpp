#include <string>
#include <iostream>
#include "ws.h"


// This adapts functions in ../waveshare_lib (code written by waveshare)

Ws::Ws(bool background_dark)
{
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    m_imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0)? (EPD_4IN2_V2_WIDTH / 8 ): (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;

    if((m_canvas_data = (UBYTE *)malloc(m_imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        // return -1;
    }
    
    printf("Paint_NewImage(m_canvas_data, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);\n");
    Paint_NewImage(m_canvas_data, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    
    printf("Paint_SelectImage(m_canvas_data);\n");
    Paint_SelectImage(m_canvas_data);

    printf("Paint_Clear(%s);\n", background_dark ? "BLACK" : "WHITE");
    Paint_Clear(background_dark ? BLACK : WHITE);
}

void Ws::Paint_DrawCircle(  UWORD X_Center, UWORD Y_Center, UWORD Radius,
                            UWORD Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill)
{
    if (X_Center > m_paint.Width || Y_Center >= m_paint.Height) {
        if (m_debug)
            Debug("Paint_DrawCircle Input exceeds the normal display range\r\n");
        return;
    }

    //Draw a circle from(0, R) as a starting point
    int16_t XCurrent, YCurrent;
    XCurrent = 0;
    YCurrent = Radius;

    //Cumulative error,judge the next point of the logo
    int16_t Esp = 3 - (Radius << 1 );

    int16_t sCountY;
    if (Draw_Fill == DRAW_FILL_FULL) {
        while (XCurrent <= YCurrent ) { //Realistic circles
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
                Paint_DrawPoint(X_Center + XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//1
                Paint_DrawPoint(X_Center - XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//2
                Paint_DrawPoint(X_Center - sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//3
                Paint_DrawPoint(X_Center - sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//4
                Paint_DrawPoint(X_Center - XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//5
                Paint_DrawPoint(X_Center + XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//6
                Paint_DrawPoint(X_Center + sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//7
                Paint_DrawPoint(X_Center + sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            }
            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    } else { //Draw a hollow circle
        while (XCurrent <= YCurrent ) {
            Paint_DrawPoint(X_Center + XCurrent, Y_Center + YCurrent, Color, Line_width, DOT_STYLE_DFT);//1
            Paint_DrawPoint(X_Center - XCurrent, Y_Center + YCurrent, Color, Line_width, DOT_STYLE_DFT);//2
            Paint_DrawPoint(X_Center - YCurrent, Y_Center + XCurrent, Color, Line_width, DOT_STYLE_DFT);//3
            Paint_DrawPoint(X_Center - YCurrent, Y_Center - XCurrent, Color, Line_width, DOT_STYLE_DFT);//4
            Paint_DrawPoint(X_Center - XCurrent, Y_Center - YCurrent, Color, Line_width, DOT_STYLE_DFT);//5
            Paint_DrawPoint(X_Center + XCurrent, Y_Center - YCurrent, Color, Line_width, DOT_STYLE_DFT);//6
            Paint_DrawPoint(X_Center + YCurrent, Y_Center - XCurrent, Color, Line_width, DOT_STYLE_DFT);//7
            Paint_DrawPoint(X_Center + YCurrent, Y_Center + XCurrent, Color, Line_width, DOT_STYLE_DFT);//0

            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    }
}

/******************************************************************************
function: Draw Point(Xpoint, Ypoint) Fill the color
parameter:
    Xpoint		: The Xpoint coordinate of the point
    Ypoint		: The Ypoint coordinate of the point
    Color		: Painted color
    Dot_Pixel	: point size
    Dot_Style	: point Style
******************************************************************************/
void Ws::Paint_DrawPoint(   UWORD Xpoint, UWORD Ypoint, UWORD Color,
                            DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_Style)
{
    if (Xpoint > m_paint.Width || Ypoint > m_paint.Height) {
        if (m_debug)
            Debug("Paint_DrawPoint Input exceeds the normal display range\r\n");
        return;
    }

    int16_t XDir_Num , YDir_Num;
    if (Dot_Style == DOT_FILL_AROUND) {
        for (XDir_Num = 0; XDir_Num < 2 * Dot_Pixel - 1; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num < 2 * Dot_Pixel - 1; YDir_Num++) {
                if(Xpoint + XDir_Num - Dot_Pixel < 0 || Ypoint + YDir_Num - Dot_Pixel < 0)
                    break;
                // printf("x = %d, y = %d\r\n", Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel);
                Paint_SetPixel(Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, Color);
            }
        }
    } else {
        for (XDir_Num = 0; XDir_Num <  Dot_Pixel; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num <  Dot_Pixel; YDir_Num++) {
                Paint_SetPixel(Xpoint + XDir_Num - 1, Ypoint + YDir_Num - 1, Color);
            }
        }
    }
}


void Ws::Paint_SetPixel(UWORD Xpoint, UWORD Ypoint, UWORD Color)
{
    if(Xpoint > m_paint.Width || Ypoint > m_paint.Height){
        if (m_debug)
            Debug("Exceeding display boundaries\r\n");
        return;
    }      
    UWORD X, Y;
    switch(m_paint.Rotate) {
    case 0:
        X = Xpoint;
        Y = Ypoint;  
        break;
    case 90:
        X = m_paint.WidthMemory - Ypoint - 1;
        Y = Xpoint;
        break;
    case 180:
        X = m_paint.WidthMemory - Xpoint - 1;
        Y = m_paint.HeightMemory - Ypoint - 1;
        break;
    case 270:
        X = Ypoint;
        Y = m_paint.HeightMemory - Xpoint - 1;
        break;
    default:
        return;
    }
    
    switch(m_paint.Mirror) {
    case MIRROR_NONE:
        break;
    case MIRROR_HORIZONTAL:
        X = m_paint.WidthMemory - X - 1;
        break;
    case MIRROR_VERTICAL:
        Y = m_paint.HeightMemory - Y - 1;
        break;
    case MIRROR_ORIGIN:
        X = m_paint.WidthMemory - X - 1;
        Y = m_paint.HeightMemory - Y - 1;
        break;
    default:
        return;
    }

    if(X > m_paint.WidthMemory || Y > m_paint.HeightMemory){
        if (m_debug)
            Debug("Exceeding display boundaries\r\n");
        return;
    }
    
    if(m_paint.Scale == 2){
        UDOUBLE Addr = X / 8 + Y * m_paint.WidthByte;
        UBYTE Rdata = m_paint.Image[Addr];
        if(Color == BLACK)
            m_paint.Image[Addr] = Rdata & ~(0x80 >> (X % 8));
        else
            m_paint.Image[Addr] = Rdata | (0x80 >> (X % 8));
    }else if(m_paint.Scale == 4){
        UDOUBLE Addr = X / 4 + Y * m_paint.WidthByte;
        Color = Color % 4;//Guaranteed color scale is 4  --- 0~3
        UBYTE Rdata = m_paint.Image[Addr];
        Rdata = Rdata & (~(0xC0 >> ((X % 4)*2)));//Clear first, then set value
        m_paint.Image[Addr] = Rdata | ((Color << 6) >> ((X % 4)*2));
    }else if(m_paint.Scale == 6 || m_paint.Scale == 7 || m_paint.Scale == 16){
		UDOUBLE Addr = X / 2  + Y * m_paint.WidthByte;
		UBYTE Rdata = m_paint.Image[Addr];
		Rdata = Rdata & (~(0xF0 >> ((X % 2)*4)));//Clear first, then set value
		m_paint.Image[Addr] = Rdata | ((Color << 4) >> ((X % 2)*4));
		// printf("Add =  %d ,data = %d\r\n",Addr,Rdata);
	}
}

void Ws::Debug(std::string str)
{
    if (m_debug)
        std::cout << str << std::endl;
}

void Ws::Paint_Clear(UWORD Color)
{	
	if(m_paint.Scale == 2) {
		for (UWORD Y = 0; Y < m_paint.HeightByte; Y++) {
			for (UWORD X = 0; X < m_paint.WidthByte; X++ ) {//8 pixel =  1 byte
				UDOUBLE Addr = X + Y*m_paint.WidthByte;
				m_paint.Image[Addr] = Color;
			}
		}		
    }else if(m_paint.Scale == 4) {
        for (UWORD Y = 0; Y < m_paint.HeightByte; Y++) {
			for (UWORD X = 0; X < m_paint.WidthByte; X++ ) {
				UDOUBLE Addr = X + Y*m_paint.WidthByte;
				m_paint.Image[Addr] = (Color<<6)|(Color<<4)|(Color<<2)|Color;
			}
		}		
	}else if(m_paint.Scale == 6 || m_paint.Scale == 7 || m_paint.Scale == 16) {
		for (UWORD Y = 0; Y < m_paint.HeightByte; Y++) {
			for (UWORD X = 0; X < m_paint.WidthByte; X++ ) {
				UDOUBLE Addr = X + Y*m_paint.WidthByte;
				m_paint.Image[Addr] = (Color<<4)|Color;
			}
		}		
	}
}

void Ws::Paint_NewImage(UBYTE *image, UWORD Width, UWORD Height, UWORD Rotate, UWORD Color)
{
    m_paint.Image = NULL;
    m_paint.Image = image;

    m_paint.WidthMemory = Width;
    m_paint.HeightMemory = Height;
    m_paint.Color = Color;    
    m_paint.Scale = 2;
    m_paint.WidthByte = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);
    m_paint.HeightByte = Height;    
//    printf("WidthByte = %d, HeightByte = %d\r\n", m_paint.WidthByte, m_paint.HeightByte);
//    printf(" EPD_WIDTH / 8 = %d\r\n",  122 / 8);
   
    m_paint.Rotate = Rotate;
    m_paint.Mirror = MIRROR_NONE;
    
    if(Rotate == ROTATE_0 || Rotate == ROTATE_180) {
        m_paint.Width = Width;
        m_paint.Height = Height;
    } else {
        m_paint.Width = Height;
        m_paint.Height = Width;
    }
}

void Ws::Paint_SelectImage(UBYTE *image)
{
    m_paint.Image = image;
}