#include "timer.hpp"
#include "app.hpp"
#include "input.hpp"
#include <sstream>
#include <cmath>

Timer::Timer(Text& text)
    : text(text)
{
    last_render_ms = 0;
    started_at = 0;
    reset();
}

void Timer::update()
{
    if (Input::pressed(InputKey::start_stop_reset) && !running && at_ms == 0) {
        start();
    } else if (Input::pressed(InputKey::start_stop_reset) && running) {
        stop();
    } else if (Input::pressed(InputKey::start_stop_reset)) {
        reset();
    }

    if (running) {
        at_ms = SDL_GetTicks() - started_at;

        if (at_ms / 1000 != last_render_ms / 1000) {
            render();
        }
    }
}

void Timer::start()
{
    running = true;
    started_at = SDL_GetTicks();
    render();
}

void Timer::stop()
{
    running = false;
    render();
}

void Timer::reset()
{
    running = false;
    at_ms = 0;
    render();
}

int Timer::get_hours()
{
    return at_ms / 1000 / 60 / 60;
}

int Timer::get_minutes()
{
    return at_ms / 1000 / 60 % 60;
}

int Timer::get_seconds()
{
    return at_ms / 1000 % 60;
}

int Timer::get_millisec()
{
    return at_ms % 1000;
}

void Timer::render()
{
    std::stringstream ss;
    if (running || at_ms == 0) {
        ss << get_minutes() << ':';
        ss.fill('0');
        ss.width(2);
        ss << get_seconds();
    } else {
        ss << get_minutes() << ':';
        ss.fill('0');
        ss.width(2);
        ss << get_seconds() << '.';
        ss.fill('0');
        ss.width(2);
        ss << round(get_millisec() / 10);
    }
    text.set(ss.str());
    last_render_ms = at_ms;
    App::render();
}
