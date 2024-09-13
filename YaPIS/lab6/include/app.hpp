#pragma once

#include "edge.hpp"
#include <iostream>
#include <limits>
#include <vector>

namespace lab {
    class App {
        public:
        static void run() {
            std::vector<std::vector<Node::Edge>> graph = {
                {{1, 4}, {2, 1}},
                {{0, 4}, {2, 2}, {3, 1}},
                {{0, 1}, {1, 2}, {3, 5}},
                {{1, 1}, {2, 5}}
            };

            Node::Values values{
                .start = 0,
                .target = 3,
                .cur_distance = 0,
                .min_distance = std::numeric_limits<int>::max()
            };
            values.visited.resize(graph.size(), false);

            Node::dfs_recursive(
                values.start, 
                values.target, 
                graph, 
                values.visited,
                values.path,
                values.cur_distance,
                values.min_distance,
                values.best_path
            );
            std::cout << "Recursive: " << std::endl;

            if(values.min_distance == std::numeric_limits<int>::max()) {
                std::cout << "path from " << values.start << " to " << values.target << "doesn't exist" << std::endl;
            } else {
                std::cout << "Shorter path: " << values.min_distance << ": ";
                for(int node: values.best_path) {
                    std::cout << node << ' ';
                }
                std::cout << std::endl;
            }

            std::cout << "Non-recursive: " << std::endl;
            Node::dfs_non_recursive(values.start, values.target, graph);
        }
    };
}