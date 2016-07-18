#include "timer.hpp"
#include "app.hpp"
#include "input.hpp"
#include <iostream>

Timer::Timer(Text& text)
    : text(text)
{
    last_render.ms = 0;
    started_at.ms = 0;
    current_segment = 0;
    reset();

    segments.push_back(Segment("Enter tree"));
    segments.push_back(Segment("Get bottle"));
    segments.push_back(Segment("Gohma"));
    segments.push_back(Segment("Ganondorf", Time(200, 27, 13)));
    segments.push_back(Segment("Escape tower", Time(800, 35, 15)));
    segments.push_back(Segment("Ganon", Time(600, 11, 19)));

    double i = 0;
    for (Segment& s : segments) {
        Text* t = new Text(s.name.c_str(), "font", 18);
        t->pos = Coord{10, i};
        t->set_center(Coord{-1, -1});

        std::string str;
        if (s.time_exists) {
            str = s.time_best_run.to_str();
        } else {
            str = std::string("-");
        }
        Text* u = new Text(str, "font", 18);
        u->pos = Coord{(double)App::get_window_width() - 10, i};
        u->set_center(Coord{1, -1});

        i += 22;
    }
}

void Timer::update()
{
    if (Input::pressed(InputKey::start_stop_reset)) {
        if (!running && time.ms == 0) {
            start();
        } else if (!running) {
            reset();
        } else if (segments.size() != 0 && current_segment != segments.size() - 1) {
            segments[current_segment].this_time = time;
            current_segment++;
        } else {
            stop();
        }
    }

    if (Input::pressed(InputKey::reset)) {
        reset();
    }

    if (running) {
        time.ms = SDL_GetTicks() - started_at.ms;

        if (time.ms / 1000 != last_render.ms / 1000) {
            render();
        }
    }
}

void Timer::start()
{
    running = true;
    started_at.ms = SDL_GetTicks();
    text.set_color(0x66, 0xcc, 0x33, 0xff);
    render();
}

void Timer::stop()
{
    running = false;
    text.set_color(0x99, 0x99, 0x99, 0xff);
    render();
}

void Timer::reset()
{
    running = false;
    time.ms = 0;
    current_segment = 0;
    text.set_color(0x99, 0x99, 0x99, 0xff);
    render();
}

void Timer::render()
{
    text.set(time.to_str());
    last_render.ms = time.ms;
    App::render();
}
