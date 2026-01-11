#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdint.h>

#include "epsim.h"
#include "stb_image_write.h"


// Epsim: E-paper simulator
// Generate a PNG of what would appear on a e-ink display by generating PNGs. 

// Constructor
Epsim::Epsim(int w, int h) : m_width(w), m_height(h), pixels(w*h, 0) {}

// pixel:    1   2   3   4  |  5   6   7   8
// bit:     7 6 5 4 3 2 1 0 | 7 6 5 4 3 2 1 0

void Epsim::Image2Vector(uint8_t *Image, std::size_t len)
{
    std::cout << "len: " << len << std::endl;
    if (len > 0 && Image == nullptr)
    {
        throw std::invalid_argument("Data in Image buffer is null!");
    }

    for (int i = 0; i < len; ++i)
    {
        // I'm picking out every bit and converting it to a black/white
        // (8 bit value in Image) & 0b1000000,
        //                          0b01000000,
        // then bit shifting it to the right

        uint8_t waveshare_8_pixels = Image[i];

        for (int j = 0; j < 8; ++j)
        {
            uint8_t p = waveshare_8_pixels & (0b10000000 >> j);
            pixels[8*i + j] = p >> (7 - j);
        }
        
        // uint8_t p1 = waveshare_8_pixels & 0b10000000;
        // uint8_t p2 = waveshare_8_pixels & 0b01000000;
        // uint8_t p3 = waveshare_8_pixels & 0b00100000;
        // uint8_t p4 = waveshare_8_pixels & 0b00010000;
        // uint8_t p5 = waveshare_8_pixels & 0b00001000;
        // uint8_t p6 = waveshare_8_pixels & 0b00000100;
        // uint8_t p7 = waveshare_8_pixels & 0b00000010;
        // uint8_t p8 = waveshare_8_pixels & 0b00000001;
        

        // pixels[8*i + 0] = p1 >> 7;
        // pixels[8*i + 1] = p2 >> 6;
        // pixels[8*i + 2] = p3 >> 5;
        // pixels[8*i + 3] = p4 >> 4;
        // pixels[8*i + 4] = p5 >> 3;
        // pixels[8*i + 5] = p6 >> 2;
        // pixels[8*i + 6] = p7 >> 1;
        // pixels[8*i + 7] = p8;

    }
        // convert 1 and 0 to 255 and 0
    for (auto &p : pixels)
    {
        switch (p)
        {
            case 0b0:
                p = 0x00;
                break;
            case 0b1:
                p = 0xFF;
                break;
            default:
                break;
        }
    }
}

void Epsim::Save(std::string f_filename)
{
    

    /* Test Image */
    // int count = 0;
    // for (auto& p : pixels)
    // {
    //     if ((count/m_width)%2 == 0)
    //     {
    //         p = count%2 ? 0 : 255;
    //     }
    //     else
    //     {
    //         p = count%2 ? 255 : 0;
    //     }
    //     ++count;
    // }

    // fill pixels with grayscale
    std::stringstream ss;
    // ss << "./simages/" << f_filename;
    ss << f_filename;
    const char* file = ss.str().c_str();
    stbi_write_png(file, m_width, m_height, 1, pixels.data(), m_width);
    std::cout << "Saved " << f_filename << "!" << std::endl;
}