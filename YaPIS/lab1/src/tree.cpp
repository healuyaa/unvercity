#include <iostream>

#include "tree.hpp"

namespace tree {
    Node* insert(Node* root, const std::string& id) {
        if(root == nullptr) {
            root = new Node(id[0]);
            root->ids.push_back(id);
            return root;
        }

        if(id[0] < root->key) {
            root->left = insert(root->left, id);
        } else if(id[0] > root->key) {
            root->right = insert(root->right, id);
        } else {
            root->ids.push_back(id);
        }

        return root;
    }

    bool search(Node* root, const std::string& id) {
        if(root == nullptr) return false;

        if(id[0] < root->key) {
            return search(root->left, id);
        } else if(id[0] > root->key) {
            return search(root->right, id);
        } else {
            for(const auto& stored_id: root->ids) {
                if(stored_id == id) return true;
            }
        }

        return false;
    }

    void print(Node* root, std::string indent, bool is_left) {
        if (root != nullptr) {
            std::cout << indent;
            
            if (is_left) {
                std::cout << "|-- ";
                indent += "|   ";
            } else {
                std::cout << "|- ";
                indent += "    ";
            }
            
            std::cout << root->key << " (";
            for (size_t i = 0; i < root->ids.size(); ++i) {
                std::cout << root->ids[i];
                if (i != root->ids.size() - 1) std::cout << ", ";
            }
            std::cout << ")" << std::endl;

            print(root->left, indent, true);
            print(root->right, indent, false);
        }
    }
}