#include "segment.hpp"
#include "time.hpp"
#include "text.hpp"
#include "app.hpp"
#include <string>
#include <sstream>

Segment::Segment(const char* name)
    : Segment(name, 0)
{
    best_time_exists = false;
    this_time_exists = false;
    this_best_time_exists = false;
    update_time_text();
}

Segment::Segment(const char* name, Time time_best_run)
    : name(Text(std::string(name), "font", 18))
    , time_best_run(time_best_run)
    , time_text(Text(time_best_run.to_str(), "font", 18))
{
    this->name.set_center(Coord{-1, -1});
    this->name.parent = this;
    this->best_time_exists = true;
    this->this_time_exists = false;
    this->this_best_time_exists = false;
    this->time_text.pos = Coord{(double)App::get_window_width(), 0};
    this->time_text.set_center(Coord{1.0, -1.0});
    this->time_text.parent = this;
    update_time_text();
}

void Segment::set_this_time(Time new_time)
{
    this->this_time = new_time;
    this->this_time_exists = true;
    update_time_text();
}

void Segment::set_name(const char* new_name)
{
    name.set(new_name);
}

void Segment::update_time_text()
{
    if (this_time_exists) {
        if (best_time_exists) {
            int diff_ms = this_time.ms - time_best_run.ms;
            if (this_best_time_exists) {
                diff_ms = this_time.ms - this_best_time.ms;
            }
            std::stringstream ss;
            if (diff_ms < 0) {
                Time t(-diff_ms);
                if (-diff_ms < 60000) {
                    ss << '-' << t.to_str(1, 2);
                } else {
                    ss << '-' << t.to_str(1, 0);
                }
                time_text.set_color(0x66, 0xff, 0x33, 0xff);
            } else {
                Time t(diff_ms);
                if (diff_ms < 60000) {
                    ss << '+' << t.to_str(1, 2);
                } else {
                    ss << '+' << t.to_str(1, 0);
                }
                time_text.set_color(0xff, 0x66, 0x33, 0xff);
            }
            this->time_text.set(ss.str());
        } else {
            this->time_text.set(this_time.to_str());
        }
    } else if (this_best_time_exists) {
        this->time_text.set(this_best_time.to_str(2, 0));
    } else if (best_time_exists) {
        this->time_text.set(time_best_run.to_str(2, 0));
    } else {
        this->time_text.set("-");
    }
}
