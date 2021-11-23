#include "../common.h"

#include <vector>
#include <string>
#include <map>

using namespace std;

extern "C" float shortest_length(graph& g, const std::string& src, 
        const std::string& dst)
{
    const int INF = 1e9;
    //vector<map<string, float>> dist(g.size());
    map<string, float> dist;
    for (auto it = g.begin(); it != g.end(); it++) {
        dist[it->first] = INF;
    }
    dist[src] = 0;

    for (size_t k = 0; k < g.size() - 1; k++) {
        for (auto it = g.begin(); it != g.end(); it++) {
            string v = it->first;
            for (int j = 0; j < it->second.size(); j++) {
                string u = it->second[j].first;
                float w = it->second[j].second;
                if (dist[u] != INF) {
                    dist[v] = min(dist[v], dist[u] + w);
                }
            }
        }
    }

    return dist[dst];
}
