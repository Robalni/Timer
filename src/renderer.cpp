#include "renderer.hpp"
#include <SDL.h>

Renderer::Renderer(SDL_Renderer* r)
{
    renderer = r;
}

void Renderer::update()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}
