#pragma once

#include "object.hpp"
#include <SDL.h>

class Renderer : public Object {
public:
    Renderer(SDL_Renderer* r);
    void update();

private:
    SDL_Renderer* renderer;
};
