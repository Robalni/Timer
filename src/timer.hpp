#pragma once

#include "object.hpp"
#include "text.hpp"
#include "segment.hpp"
#include "time.hpp"
#include <vector>

class Timer : public Object {
public:
    Timer(Text& text);
    void update();
    void start();
    void stop();
    void reset();

private:
    void render();

    std::vector<Segment> segments;
    unsigned int current_segment;
    Text& text;
    bool running;
    Time time;
    Time started_at;
    Time last_render;
};
