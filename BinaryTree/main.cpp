#include <iostream>
#include <string>

class Tree;

class Node {
private:
    Node *left, *right, *parent;
    friend class Tree;

public:
    Node* getLeft() { return left; }
    const Node* getLeft() { return left; }
    Node* getRight() { return right; }
    const Node* getRight { return right; }

    std::string name;

    Node() : name(""), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(const std::string& name, const Node* parent = nullptr)  
        : name(name), left(nullptr), right(nullptr), parent(parent) {}

    Node* findMin() {
        Node* node = this;
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    
    Node* findMax() {
        Node* node = this;
        while (node->right) {
            node = node->right;
        }
        return node;
    }
};

class TreeIterator;

class Tree {
private:
    Node* root;

public:
    Node* getRoot() { return root; }
    const Node* getRoot() const { return root; }

    Tree() : root(nullptr);

    Node* addNode(const std::string& name) {}

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

    Node* findMin() {
        Node* node = root;
        if (!node) {
            return nullptr;
        }
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    
    Node* findMax() {
        Node* node = root;
        if (!node) {
            return nullptr;
        }
        while (node->right) {
            node = node->right;
        }
        return node;
    }
    
    TreeIterator begin() const {
        return TreeIterator(findMin());
    }
    TreeIterator end() const {
        return TreeIterator();
    }
};
 
 
class TreeIterator: public std::iterator<std::input_iterator_tag, Node> {
private:
    Node* node;
public:
    TreeIterator(): node(nullptr) {}
    TreeIterator(Node* node_) : node(node_) {}
    
    bool operator==(const TreeIterator& other) const {
        return node == other.node;
    }
    
    bool operator!=(const TreeIterator& other) const {
        return !(*this == other);
    }

    Node& operator*() { return *node; }
    const Node& operator*() const { return *node; }
    
    TreeIterator& operator++() {
        if (node->right) {
            node = node->right->findMin();
        }
        else if (node->parent) {
            while (node->parent && node->parent->right == node) {
                node = node->parent;
            }
            if (node->parent) {
                node = node->parent;
            }
            else {
                node = nullptr; // end, root was reached from right tree
            }
        }
        else {
            node = nullptr;
        }
        return *this;
    }
    
    TreeIterator operator++(int) {
        TreeIterator old(node);
        ++*this;
        return old;
    }

    TreeIterator& operator--() {
        Node* node = root;
        if (node->left) {
            node = node->left->findMax();
        }
        else if (node->parent) {
            while (node->parent && node->parent->left == node) {
                node = node->parent;
            }
            if (node->parent) {
                node = node->parent;
            }
            else {
                node = nullptr; // end, root was reached from left tree
            }
        }
        else {
            node = nullptr;
        }

        return *this;
    }

    TreeIterator operator--(int) {
        TreeIterator old(node);
        --*this;
        return old;
    }
};
