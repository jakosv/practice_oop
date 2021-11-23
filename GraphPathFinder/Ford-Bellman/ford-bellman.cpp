#include "../common.h"

#include <vector>
#include <string>
#include <map>

using namespace std;

extern "C" float shortest_length(graph& g, const std::string& src, 
        const std::string& dst)
{
    const int INF = 1e9;
    vector<map<string, float>> dist(g.size());
    for (int k = 0; k < g.size(); k++) {
        for (auto it = g.begin(); it != g.end(); it++) {
            dist[k][it->first] = INF;
        }
    }
    dist[0][src] = 0;

    for (size_t k = 0; k < g.size() - 1; k++) {
        for (auto it = g.begin(); it != g.end(); it++) {
            string v = it->first;
            for (int j = 0; j < it->second.size(); j++) {
                string u = it->second[j].first;
                float w = it->second[j].second;
                if (dist[k][u] != INF) {
                    dist[k+1][v] = min(dist[k+1][v], dist[k][u] + w);
                }
            }
        }
    }

    float ans = INF;
    for (size_t k = 0; k < g.size(); k++) {
        ans = min(ans, dist[k][dst]);
    }

    return ans;
}
