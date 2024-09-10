#pragma once

#include <string>
#include <vector>

namespace tree {
    struct Node {
        Node(char k) : key(k), left(nullptr), right(nullptr) {}

        char key;
        std::vector<std::string> ids;
        Node* left;
        Node* right;
    };

    Node* insert(Node* root, const std::string& id);
    bool search(Node* root, const std::string& id);
    void print(Node* root, std::string indent = "", bool is_left = true);
}