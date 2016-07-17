#include "object.hpp"
#include "app.hpp"
#include <iostream>
#include <cstring>

Object::Object()
{
    App::add_object(this);
}

Object::~Object()
{
}

double Object::get_abs_x()
{
    return pos.x;
}

double Object::get_abs_y()
{
    return pos.y;
}

void Object::update()
{
}

void Object::set_center(Coord c)
{
    center = c;
}
