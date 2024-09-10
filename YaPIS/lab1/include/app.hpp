#pragma once

#include <iostream>

#include "tree.hpp"
#include "tools.hpp"

namespace lab {
    class App {
        public:
        static void start() {
            std::string path = "../test1.txt";
            auto ids = tools::read(path);

            tree::Node* root = nullptr;
            for(const auto& id: ids) {
                root = tree::insert(root, id);
            }

            std::string search_id = "10";
            std::cout << "id for search: " << search_id << std::endl;

            if(tree::search(root,search_id)) {
                std::cout << "yes";
            } else {
                std::cout << "no";
            }
            std::cout << std::endl;

            // std::cout << "Tree" << std::endl;
            // tree::print(root);
        }
    };
}