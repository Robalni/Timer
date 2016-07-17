#include "app.hpp"
#include "object.hpp"
#include "input.hpp"
#include <list>
#include <SDL.h>
#include <SDL_ttf.h>

SDL_Window* App::window;
SDL_Renderer* App::renderer;
SDL_Joystick* App::joystick;
std::list<Object*> App::objects;
bool App::will_render = false;
double App::delta_time;
int App::current_tick;
int App::next_frame_tick;
int App::fps_wanted;

void App::init()
{
    int win_width = 200;
    int win_height = 70;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    TTF_Init();
    window = SDL_CreateWindow("Timer", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              win_width, win_height,
                              SDL_WINDOW_RESIZABLE);
    if (!window) {
        throw;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        throw;
    }
    SDL_RenderSetLogicalSize(renderer, win_width, win_height);
    joystick = SDL_JoystickOpen(0);
    fps_wanted = 100;
}

void App::quit()
{
    while (!objects.empty()) {
        objects.pop_back();
    }
    SDL_JoystickClose(joystick);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

void App::main_loop()
{
    SDL_RenderClear(renderer);
    while (true) {
        Input::read();
        for (Object* obj : objects) {
            obj->update();
        }
        if (will_render || true) {
            render_now();
        }
        sleep();
    }
}

void App::render()
{
    will_render = true;
}

void App::render_now()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    will_render = false;
}

void App::sleep()
{
    int new_tick = SDL_GetTicks();
    delta_time = (new_tick - current_tick) / 1000.0;
    current_tick = new_tick;
    next_frame_tick += 1000.0 / fps_wanted;
    if (next_frame_tick < current_tick) {
        next_frame_tick = current_tick;
    }
    SDL_Delay(next_frame_tick - current_tick);
}

void App::add_object(Object* obj)
{
    objects.push_back(obj);
}

void App::remove_object(Object* obj)
{
    delete obj;
    objects.remove(obj);
}

int App::get_window_width()
{
    int w;
    SDL_GetRendererOutputSize(renderer, &w, nullptr);
    return w;
}

int App::get_window_height()
{
    int h;
    SDL_GetRendererOutputSize(renderer, nullptr, &h);
    return h;
}
