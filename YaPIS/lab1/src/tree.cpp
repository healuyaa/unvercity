#include <iostream>
#include <algorithm>

#include "tree.hpp"

namespace tree {
    Node* insert(Node* root, const std::string& id) {
        if (root == nullptr) {
            root = new Node(id[0]);
            root->ids.push_back(id);
            return root;
        }

        if (id[0] < root->key) {
            root->left = insert(root->left, id);
        } else if (id[0] > root->key) {
            root->right = insert(root->right, id);
        } else {
            if (std::find(root->ids.begin(), root->ids.end(), id) == root->ids.end()) {
                root->ids.push_back(id);
            }
        }

        return root;
    }

    std::string search(Node* root, const std::string& id) {
        if (root == nullptr) return none_;

        if (id[0] < root->key) {
            return search(root->left, id);
        } else if (id[0] > root->key) {
            return search(root->right, id);
        } else {
            auto it = std::find(root->ids.begin(), root->ids.end(), id);
            if (it != root->ids.end()) {
                return *it;
            } else {
                return none_;
            }
        }
    }


    Node* remove(Node* root, const std::string& id) {
        if (root == nullptr) return nullptr;

        if (id[0] < root->key) {
            root->left = remove(root->left, id);
        } else if (id[0] > root->key) {
            root->right = remove(root->right, id);
        } else {
            auto it = std::find(root->ids.begin(), root->ids.end(), id);
            if (it != root->ids.end()) {
                root->ids.erase(it);
            }

            if (root->ids.empty()) {
                if (root->left == nullptr && root->right == nullptr) {
                    delete root;
                    return nullptr;
                } else if (root->left == nullptr) {
                    Node* temp = root->right;
                    delete root;
                    return temp;
                } else if (root->right == nullptr) {
                    Node* temp = root->left;
                    delete root;
                    return temp;
                } else {                    
                    Node* successor = root->right;
                    while (successor->left != nullptr) {
                        successor = successor->left;
                    }
                    root->key = successor->key;
                    root->ids = successor->ids;
                    root->right = remove(root->right, successor->ids[0]);
                }
            }
        }

        return root;
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
