#pragma once

#include "object.hpp"
#include "text.hpp"

class Timer : public Object {
public:
    Timer(Text& text);
    void update();
    void start();
    void stop();
    void reset();
    int get_hours();
    int get_minutes();
    int get_seconds();
    int get_millisec();

private:
    void render();

    Text& text;
    bool running;
    int64_t started_at;
    int64_t at_ms;
    int64_t last_render_ms;
};
