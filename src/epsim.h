#pragma once

#include <string>
#include <vector>

class Epsim {
public:
    int m_width;
    int m_height;

    // Waveshare stores 4 pixel data in 2 bit chunks. 0000 0000 = 4 pixels.
    std::vector<uint8_t> pixels;
    

    Epsim(int f_width, int f_height);
    void Image2Vector(uint8_t *Image, std::size_t len);
    void Save(std::string f_filename);
};