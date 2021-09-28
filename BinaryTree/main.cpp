#include <string>

class Node {
public:
    std::string name;
    Node* left;
    Node* right;
    Node* parent;

    Node() : name(""), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(const std::string name, const Node* left, const Node* right, 
                                                    const Node* parent)  
        : name(name), left(left), right(right), parent(parent) {}
};

class Tree {
public:
    Node* root;

    Tree() : root(nullptr);
    Node* addNode(const std::string& name);
    Node* findNode(const std::string& name) {
        for (auto node = root; node;) {
            auto res = name.compare(node->name);
            if (res == 0) {
                return node->name;
            }
            else if (res < 0) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
    }

    Node* findClosest(const std::string& name) {
        Node* ans = nullptr;
        for (auto node = root; node;) {
            auto res = name.compare(node->name);
            if (res == 0) {
                if (node->right != nullptr)
                    return node->right;
                else
                    return ans;
            }
            if (res < 0) {
                if (node->right != nullptr) {
                    ans = node->right;
                }
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return ans;
    }

    void deleteNode(Node* node) {
        Node* closestMin = node->left;

        // find max node in left subtree of node being deleted 
        for (auto temp = node->left; temp;) {
            closestMin = temp; 
            temp = temp->right;
        }
        
        // if closestMin has subtree
        closestMin->parent->right = closestMin->left; 

        // changing node to be deleted to max node in left subtree
        closestMin->parent = node->parent;
        closestMin->left = node->left;
        closestMin->right = node->right;

        // find where is node (left or right subtree)
        auto compareWithParent = node->name.compare(node->parent->name);
        if (compareWithParent < 0) {
            node->parent->left = closestMin;
        }
        else {
            node->parent->right = closestMin;
        }

        delete node;
    }
};
