#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "epsim.h"
#include "stb_image_write.h"

// Epsim: E-paper simulator
// Generate a PNG of what would appear on a e-ink display by generating PNGs. 


// Constructor
Epsim::Epsim(int f_width, int f_height)
{
    m_width = f_width;
    m_height = f_height;
}

void Epsim::Generate(std::string f_filename)
{
    std::vector<unsigned char> pixels(m_width*m_height, 0);

    int count = 0;
    for (auto& p : pixels)
    {
        if ((count/m_width)%2 == 0)
        {
            p = count%2 ? 0 : 255;
        }
        else
        {
            p = count%2 ? 255 : 0;
        }
        
        

        ++count;
    }

    // fill pixels with grayscale
    std::stringstream ss;
    // ss << "./simages/" << f_filename;
    ss << f_filename;
    const char* file = ss.str().c_str();
    stbi_write_png(file, m_width, m_height, 1, pixels.data(), m_width);
    std::cout << "Saved " << f_filename << "!" << std::endl;
}