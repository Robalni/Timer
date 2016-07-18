#include "segment.hpp"
#include "time.hpp"
#include <string>

Segment::Segment(const char* name)
{
    this->name = std::string(name);
    this->time_exists = false;
}

Segment::Segment(const char* name, Time time_best_run)
{
    this->name = std::string(name);
    this->time_best_run = time_best_run;
    this->time_exists = true;
}
