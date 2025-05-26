#pragma once
#pragma once

namespace SiaRift
{
    struct SiaRect
    {
        // Data members (public by default in a struct)
        int left{};
        int top{};
        int width{};
        int height{};

        // Constructors (public by default in a struct)
        SiaRect(): left(0), top(0), width(256), height(256){}
        SiaRect(int width, int height) : left(0), top(0), width(width), height(height) {}
        SiaRect(int left, int top, int width, int height) : left(left), top(top), width(width), height(height) {}

    
    };
}