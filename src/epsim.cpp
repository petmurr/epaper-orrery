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

void Epsim::Image2Vector(uint8_t *Image, std::size_t len)
{
    std::cout << "len: " << len << std::endl;
    if (len > 0 && Image == nullptr)
    {
        throw std::invalid_argument("Data in Image buffer is null!");
    }

    pixels = std::vector<unsigned char>(Image, Image + len);
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