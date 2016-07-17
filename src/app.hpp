#pragma once

#include "object.hpp"
#include <list>
#include <SDL.h>

class App {
public:
    static void init();
    static void quit();
    static void main_loop();
    static void sleep();
    static void add_object(Object* obj);
    static void remove_object(Object* obj);
    static int get_window_width();
    static int get_window_height();
    static void render();

    static SDL_Renderer* renderer;
    static bool will_render;

private:
    static void render_now();

    static std::list<Object*> objects;

    static SDL_Window* window;
    static SDL_Joystick* joystick;

    static double delta_time;
    static int current_tick;
    static int next_frame_tick;
    static int fps_wanted;
};
