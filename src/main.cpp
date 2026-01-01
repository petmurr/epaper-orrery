#include <iostream>
#include "epsim.h"

int main() {
    std::cout << "---- epaper-orrery ----" << std::endl;

    Epsim e(400, 300); 
    e.Generate("image.png");

    return 0;
}