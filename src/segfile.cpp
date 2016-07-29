#include "segfile.hpp"
#include "time.hpp"
#include <fstream>
#include <string>
#include <iostream>

bool read_segments_from_file(const char* fname, std::vector<Segment>& vec)
{
    std::ifstream ifs(fname);
    std::string line;
    while (std::getline(ifs, line)) {
        int delim = line.find_first_of(' ', line.find_first_not_of(' '));
        std::string time_str = line.substr(0, delim);
        std::string name = line.substr(delim + 1);
        Time time = Time(time_str);
        vec.emplace_back(name.c_str(), time);
    }
    return true;
}

bool save_segments_to_file(const char* fname, std::vector<Segment>& vec)
{
    std::ofstream ofs(fname);
    for (Segment& s : vec) {
        ofs << s.time_best_run.to_str(1, 3) << ' ' << s.name.get() << std::endl;
    }
    return true;
}
