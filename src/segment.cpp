#include "segment.hpp"
#include "time.hpp"
#include "text.hpp"
#include "app.hpp"
#include <string>

Segment::Segment(const char* name)
    : Segment(name, 0)
{
    time_exists = false;
    update_time_text();
}

Segment::Segment(const char* name, Time time_best_run)
    : name(Text(std::string(name), "font", 18))
    , time_best_run(time_best_run)
    , time_text(Text(time_best_run.to_str(), "font", 18))
{
    this->name.set_center(Coord{-1, -1});
    this->name.parent = this;
    this->time_exists = true;
    this->time_text.pos = Coord{(double)App::get_window_width(), 0};
    this->time_text.set_center(Coord{1.0, -1.0});
    this->time_text.parent = this;
}

void Segment::update_time_text()
{
    if (time_exists) {
        this->time_text.set(time_best_run.to_str());
    } else {
        this->time_text.set("-");
    }
}
