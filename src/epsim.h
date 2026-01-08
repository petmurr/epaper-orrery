#pragma once

#include <string>
#include <vector>

class Epsim {
public:
    int m_width;
    int m_height;

    std::vector<unsigned char> pixels;

    Epsim(int f_width, int f_height);
    void Image2Vector(uint8_t *Image, std::size_t len);
    void Save(std::string f_filename);
};