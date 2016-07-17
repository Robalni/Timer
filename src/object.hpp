#pragma once

#include "coord.hpp"

class Object {
public:
    Object();
    virtual ~Object();
    double get_abs_x();
    double get_abs_y();
    virtual void update();
    virtual void set_center(Coord c);

    Coord pos;

protected:
    Coord center;
};
