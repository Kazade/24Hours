#ifndef TWF_TYPES_H
#define TWF_TYPES_H

struct Point {
    Point(int32_t X, int32_t Y):
        x(X), y(Y) {}
        
    int32_t x;
    int32_t y;
};

struct Vec2f {
    Vec2f(float X, float Y):
        x(X), y(Y) {}

    float x;
    float y;
};

#endif
