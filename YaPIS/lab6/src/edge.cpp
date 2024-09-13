#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>

#include "edge.hpp"

namespace Node {
    void dfs_recursive(int node, int target, std::vector<std::vector<Edge>>& graph, std::vector<bool>& visited, std::vector<int>& path, int& current_distance, int& min_distance, std::vector<int>& best_path) {
        visited[node] = true;
        path.push_back(node);
        
        if (node == target) {
            if (current_distance < min_distance) {
                min_distance = current_distance;
                best_path = path;
            }
        } else {
            for (const Edge& edge : graph[node]) {
                if (!visited[edge.to]) {
                    current_distance += edge.weight;
                    dfs_recursive(edge.to, target, graph, visited, path, current_distance, min_distance, best_path);
                    current_distance -= edge.weight;
                }
            }
        }
        
        visited[node] = false;
        path.pop_back();
    }

    void dfs_non_recursive(int start, int target, std::vector<std::vector<Edge>> &graph) {
        std::vector<int> best_path;
        int min_distance = std::numeric_limits<int>::max();

        std::stack<std::pair<int, std::pair<int, std::vector<int>>>> s;
        s.push({start, {0, {start}}});

        while (!s.empty()) {
            auto [node, info] = s.top(); s.pop();
            int current_distance = info.first;
            std::vector<int> path = info.second;

            if (node == target) {
                if (current_distance < min_distance) {
                    min_distance = current_distance;
                    best_path = path;
                }
            } else {
                for (const Edge& edge : graph[node]) {
                    if (std::find(path.begin(), path.end(), edge.to) == path.end()) {
                        std::vector<int> new_path = path;
                        new_path.push_back(edge.to);
                        s.push({edge.to, {current_distance + edge.weight, new_path}});
                    }
                }
            }
        }

        if (min_distance == std::numeric_limits<int>::max()) {
            std::cout << "Path " << start << " to " << target << " non realistic." << std::endl;
        } else {
            std::cout << "shorter path " << min_distance << ": ";
            for (int node : best_path) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }
}