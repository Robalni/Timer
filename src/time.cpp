#include "time.hpp"
#include <cmath>
#include <sstream>
#include <string>

Time::Time(int64_t ms, int64_t s, int64_t m, int64_t h)
{
    set(ms, s, m, h);
}

Time::Time(std::string& str)
{
    int ms = 0, s = 0, m = 0, h = 0;
    size_t start, len;
    bool last = false;

    start = str.find_last_of('.');
    if (start != std::string::npos) {
        len = str.find_last_of("0123456789") - start;
        ms = atoi(str.substr(start + 1, len).c_str());
        for (size_t i = 0; i < 3 - len; i++) {
            ms *= 10;
        }
        start -= 1;
    }

    start = str.find_last_of(':', start);
    if (start == std::string::npos) {
        start = str.find_first_of("0123456789");
        last = true;
    } else {
        start++;
    }
    s = atoi(str.substr(start).c_str());

    if (!last) {
        start = str.find_last_of(':', start - 2);
        if (start == std::string::npos) {
            start = str.find_first_of("0123456789");
            last = true;
        } else {
            start++;
        }
        m = atoi(str.substr(start).c_str());
    }

    if (!last) {
        start = str.find_last_of(':', start - 2);
        if (start == std::string::npos) {
            start = str.find_first_of("0123456789");
        } else {
            start++;
        }
        h = atoi(str.substr(start).c_str());
    }

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

std::string Time::to_str(int length, int precision)
{
    std::stringstream ss;
    if (this->get_minutes() || length >= 2) {
        ss << this->get_minutes() << ":";
        ss.fill('0');
        ss.width(2);
    }
    ss << this->get_seconds();
    if (precision > 0) {
        ss << ".";
        ss.fill('0');
        ss.width(precision);
        ss << round(this->get_millisec() / pow(10, 3 - precision));
    }
    return ss.str();
}
