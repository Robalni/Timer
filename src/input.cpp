#include "input.hpp"
#include "app.hpp"
#include <SDL.h>

enum Action {
    none, down, hold, up
};

static Action inputs[InputKey::n_keys];

void Input::read()
{
    next_step();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            App::quit();
            break;
        case SDL_JOYBUTTONUP:
        case SDL_JOYBUTTONDOWN:
            if (event.jbutton.button == 7) {
                handle_event(InputKey::start_stop_reset, event.type);
            } else if (event.jbutton.button == 6) {
                handle_event(InputKey::reset, event.type);
            }
            break;
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE) {
                handle_event(InputKey::start_stop_reset, event.type);
            } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                handle_event(InputKey::reset, event.type);
            }
            break;
        }
    }
}

void Input::handle_event(InputKey key, int type)
{
    if ((type == SDL_KEYDOWN || type == SDL_MOUSEBUTTONDOWN
         || type == SDL_JOYBUTTONDOWN) && inputs[key] != Action::hold) {
        inputs[key] = Action::down;
    } else if (type == SDL_KEYUP || type == SDL_MOUSEBUTTONUP
               || type == SDL_JOYBUTTONUP) {
        inputs[key] = Action::up;
    }
}

bool Input::is_down(InputKey key)
{
    return inputs[key] == Action::down || inputs[key] == Action::hold;
}

bool Input::pressed(InputKey key)
{
    return inputs[key] == Action::down;
}

bool Input::released(InputKey key)
{
    return inputs[key] == Action::up;
}

void Input::next_step()
{
    for (Action& a : inputs) {
        if (a == Action::down) {
            a = Action::hold;
        } else if (a == Action::up) {
            a = Action::none;
        }
    }
}
