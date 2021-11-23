#pragma once

#include <map>
#include <string>

typedef std::map<std::string, std::map<std::string, float>> graph;

extern "C" float shortest_length(graph& g, const std::string& src, 
        const std::string& dst);
