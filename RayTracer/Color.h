#pragma once

#include "Vec3.h"

#include <iostream>
#include <fstream>

void WriteColor(std::ostream& out, Vec3 pixel_color) 
{
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}
