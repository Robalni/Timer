#include "text.hpp"
#include "app.hpp"
#include <cstring>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

Text::Text()
    : Text(std::string(""), "font", 10)
{
}

Text::Text(const char* str, const char* fontfile, int size)
    : Text(std::string(str), fontfile, size)
{
}

Text::Text(const std::string str, const char* fontfile, int size)
{
    texture = nullptr;
    color = SDL_Color{0xff, 0xff, 0xff, 0xff};
    drect.w = drect.h = drect.x = drect.y = 0;
    font = TTF_OpenFont(fontfile, size);
    if (!font) {
        std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        throw;
    }

    set(str);
}

Text::~Text()
{
    TTF_CloseFont(font);
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Text::set(std::string new_string)
{
    str = new_string;
    change();
}

void Text::change()
{
    SDL_Surface* surf;
    surf = TTF_RenderUTF8_Blended(font, str.c_str(), color);
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = SDL_CreateTextureFromSurface(App::renderer, surf);
    if (!texture) {
        throw;
    }
    SDL_FreeSurface(surf);
    if (color.a < 255) {
        SDL_SetTextureAlphaMod(texture, color.a);
    }
    int w, h;
    TTF_SizeUTF8(font, str.c_str(), &w, &h);
    drect.w = w;
    drect.h = h;
    App::render();
}


void Text::append(const char* string)
{
    str.append(string);
    change();
}

void Text::set_color(int r, int g, int b, int a)
{
    if (r >= 0) {
        color.r = r;
    }
    if (g >= 0) {
        color.g = g;
    }
    if (b >= 0) {
        color.b = b;
    }
    if (a >= 0) {
        color.a = a;
    }
    change();
}

void Text::update()
{
    drect.x = get_abs_x() - drect.w * 0.5 * (center.x + 1);
    drect.y = get_abs_y() - drect.h * 0.5 * (center.y + 1);
    SDL_RenderCopy(App::renderer, texture, nullptr, &drect);
}
