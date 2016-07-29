#pragma once

#include "segment.hpp"
#include <vector>

bool read_segments_from_file(const char* fname, std::vector<Segment>& vec);

bool save_segments_to_file(const char* fname, std::vector<Segment>& vec);
