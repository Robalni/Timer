#pragma once

#include <cstdint>
#include <string>

class Time {
public:
    Time(int64_t ms = 0, int64_t s = 0, int64_t m = 0, int64_t h = 0);
    void set(int64_t ms = 0, int64_t s = 0, int64_t m = 0, int64_t h = 0);
    int get_hours();
    int get_minutes();
    int get_seconds();
    int get_millisec();
    std::string to_str();

    int64_t ms;
};
