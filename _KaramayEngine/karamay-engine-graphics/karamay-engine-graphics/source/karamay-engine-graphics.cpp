// karamay-engine-graphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graphics/texture/gl_texture.h"

int main()
{
    std::cout << "Hello World!\n";


    auto texture_1d = gl_texture_1d::construct();
    if (texture_1d) {
        texture_1d->allocate(GL_RGBA12, 100, 5);

    }

}
