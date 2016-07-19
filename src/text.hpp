#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "object.hpp"
#include "coord.hpp"

class Text : public Object {
public:
    Text();
    Text(const char* str, const char* fontfile, int size);
    Text(const std::string str, const char* fontfile, int size);
    ~Text();
    void set(std::string new_string);
    void append(const char *str);
    void set_color(int r, int g, int b, int a);

private:
    void change();
    void update();

    std::string str;
    SDL_Color color;
    TTF_Font *font;
    SDL_Rect drect;
    SDL_Texture *texture;
    bool disabled;
};
