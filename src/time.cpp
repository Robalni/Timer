#include "time.hpp"
#include <sstream>
#include <string>

Time::Time(int64_t ms, int64_t s, int64_t m, int64_t h)
{
    set(ms, s, m, h);
}

void Time::set(int64_t ms, int64_t s, int64_t m, int64_t h)
{
    this->ms = h * 60 * 60 * 1000 + m * 60 * 1000 + s * 1000 + ms;
}

int Time::get_hours()
{
    return ms / 1000 / 60 / 60;
}

int Time::get_minutes()
{
    return ms / 1000 / 60 % 60;
}

int Time::get_seconds()
{
    return ms / 1000 % 60;
}

int Time::get_millisec()
{
    return ms % 1000;
}

std::string Time::to_str()
{
    std::stringstream ss;
    ss << this->get_minutes() << ":";
    ss.fill('0');
    ss.width(2);
    ss << this->get_seconds();
    return ss.str();
}
