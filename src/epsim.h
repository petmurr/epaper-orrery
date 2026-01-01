#pragma once

#include <string>

class Epsim {
public:
    int m_width;
    int m_height;

    Epsim(int f_width, int f_height);
    void Generate(std::string f_filename);
};