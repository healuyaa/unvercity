#pragma once

#include <iostream>

#include "tree.hpp"
#include "tools.hpp"

namespace lab {
    class App {
        public:
        static void run() {
            std::string path = "../test1.txt";
            auto ids = tools::read(path);

            tree::Node* root = nullptr;
            for(const auto& id: ids) {
                root = tree::insert(root, id);
            }

            std::string search_id = "tess";
            std::cout << "id for search: " << search_id << std::endl;

            auto ans = tree::search(root,search_id);
            if(ans != tree::none_) {
                std::cout << "Search is successful" << std::endl;
                std::cout << ans << std::endl;
            } else {
                std::cout << "Search is not successful" << std::endl;
                std::cout << tree::none_ << std::endl;
            }
            std::cout << std::endl;

            std::cout << "Tree" << std::endl;
            tree::print(root);

            tree::remove(root, "tess");
            root = tree::insert(root, "xxx");

            std::cout << std::endl;

            std::cout << "Tree" << std::endl;
            tree::print(root);
        }
    };
}