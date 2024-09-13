#pragma once

#include <vector>

namespace Node {
    struct Edge {
        int to;
        int weight;
    };

    struct Values {
        int start;
        int target;
        std::vector<bool> visited;
        std::vector<int> path, best_path;
        int cur_distance, min_distance;        
    };

    void dfs_recursive(int node, int target, std::vector<std::vector<Edge>>& graph, std::vector<bool>& visited, std::vector<int>& path, int& current_distance, int& min_distance, std::vector<int>& best_path);
    void dfs_non_recursive(int start, int target, std::vector<std::vector<Edge>>& graph);
}