#include "object.hpp"
#include "app.hpp"
#include <iostream>
#include <cstring>

Object::Object()
    : pos(Coord{0.0, 0.0})
    , parent(nullptr)
{
    App::add_object(this);
}

Object::~Object()
{
}

double Object::get_abs_x()
{
    double x = pos.x;
    Object* obj = this;
    while ((obj = obj->parent)) {
        x += obj->pos.x;
    }
    return x;
}

double Object::get_abs_y()
{
    double y = pos.y;
    Object* obj = this;
    while ((obj = obj->parent)) {
        y += obj->pos.y;
    }
    return y;
}

void Object::update()
{
}

void Object::set_center(Coord c)
{
    center = c;
}
