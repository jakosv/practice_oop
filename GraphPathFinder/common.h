#pragma once

#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<std::pair<std::string, float>>> graph;

extern "C" float shortest_length(graph& g, const std::string& src, 
        const std::string& dst);
