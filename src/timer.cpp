#include "timer.hpp"
#include "app.hpp"
#include "input.hpp"
#include "segfile.hpp"
#include <iostream>

Timer::Timer(Text& text)
    : text(text)
{
    last_render.ms = 0;
    started_at.ms = 0;
    current_segment = 0;
    reset();

    segments.reserve(60);
    read_segments_from_file("segments", segments);

    double i = 0;
    for (Segment& s : segments) {
        s.pos.y = i;
        i += 22;
    }
}

void Timer::update()
{
    if (Input::pressed(InputKey::start_stop_reset)) {
        if (!running && time.ms == 0) {
            start();
        } else if (!running) {
            save_segments_to_file("segments", segments);
            reset();
        } else if (segments.size() != 0 && current_segment != segments.size() - 1) {
            segments[current_segment].set_this_time(time);
            segments[current_segment].this_best_time_exists = true;
            segments[current_segment].this_best_time = time;
            segments[current_segment].name.set_color(0xff, 0xff, 0xff, 0xff);
            current_segment++;
            segments[current_segment].name.set_color(0x66, 0xff, 0x33, 0xff);
            text.set(time.to_str(2, 2));
            last_render.ms = time.ms + 1000;
        } else {
            stop();
        }
    }

    if (Input::pressed(InputKey::reset)) {
        reset();
    }

    if (running) {
        time.ms = SDL_GetTicks() - started_at.ms;

        if (time.ms / 1000 > last_render.ms / 1000) {
            render();
        }
    }
}

void Timer::start()
{
    running = true;
    started_at.ms = SDL_GetTicks();
    text.set_color(0x66, 0xff, 0x33, 0xff);
    segments[current_segment].name.set_color(0x66, 0xff, 0x33, 0xff);
    render();
}

void Timer::stop()
{
    if (segments.size() != 0) {
        segments[current_segment].set_this_time(time);
        segments[current_segment].this_best_time_exists = true;
        segments[current_segment].this_best_time = time;
    }
    if (segments[segments.size() - 1].this_time.ms
        < segments[segments.size() - 1].time_best_run.ms) {
        for (Segment& s : segments) {
            s.time_best_run = s.this_best_time;
        }
    }
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
    for (Segment& s : segments) {
        s.name.set_color(0xff, 0xff, 0xff, 0xff);
        if (s.this_time_exists) {
            s.this_best_time = s.time_best_run;
        }
        s.this_time_exists = false;
        s.time_text.set_color(0xff, 0xff, 0xff, 0xff);
        s.update_time_text();
    }
    render();
}

void Timer::render()
{
    if (!running && time.ms > 0) {
        text.set(time.to_str(2, 2));
    } else {
        text.set(time.to_str(2, 0));
    }
    last_render.ms = time.ms;
    App::render();
}
