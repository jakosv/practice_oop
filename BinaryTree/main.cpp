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

    void smallTurnLeft(Node* a, Node* b) {
        if (a->parent) {
            a->parent->right = b;
        }
        b->parent = a->parent;
        a->parent = b;
        if (b->left) {
            b->left->parent = a;
            a->right = b->left;
        }
        b->left = a;
    }

    void smallTurnRight(Node* a, Node* b) {
        if (a->parent) {
            a->parent->right = b;
        }
        b->parent = a->parent;
        a->parent = b;
        if (b->right) {
            b->right->parent = a;
            a->left = b->right;
        }
        b->right = a;
    }

    void bigTurnRight(Node* a, Node* b, Node* c) {
        smallTurnRight(b, c);
        smallTurnLeft(a, c);
    }

    void bigTurnLeft(Node* a, Node* b, Node* c) {
        smallTurnLeft(b, c);
        smallTurnRight(a, c);
    }

public:
    Node* getRoot() { return root; }
    const Node* getRoot() const { return root; }

    Tree() : root(nullptr);

    int getHeight(const Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int left = 0, right = 0;
        if (node->left) {
            left = getHeight(node->left) + 1;
        }
        if (node->right) {
            right = getHeight(node->right) + 1;
        }
        return left + right;
    }

    bool isBalancedTree(const Node* node) {
        int left, right;
        while (node) {
            left = getHeight(node->left);
            right = getHeight(node->right);
            if (abs(left - right) > 2) {
                return false;  
            }
        }
        return true;
    }
    
    void balancingTree(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right); 
        Node* a = node;
        if (leftHeight > rightHeight) {
            node = node->left;
            leftHeight = getHeight(node->left);
            rightHeight = getHeight(node->right);
            if (leftHeight > rightHeight) {
                smallTurnRight(node->parent, node);
            }
            else {
                bigTurnLeft(node->parent, node, node->right);
            }
        }
        else {
            node = node->right;
            leftHeight = getHeight(node->left);
            rightHeight = getHeight(node->right);
            if (leftHeight < rightHeight) {
                smallTurnLeft(node->parent, node);
            }
            else {
                bigTurnRight(node->parent, node, node->left);
            }
        }
    }

    Node* addNode(const std::string& name) {
        Node* closest = findClosest(name);
        if (closest && closest->name == name) {
            return nullptr;
        }
        Node* newNode = new Node(name, closest);
        if (closest == nullptr) {
            Node* maxNode = findMax;
            if (maxNode == nullptr) {
                root = newNode;        
                return root;
            }
            newNode->parent = maxNode;
            maxNode->right = newNode;
        }
        else {
            if (closest->left) {
                closest->left->parent = newNode;
            }
            closes->left = newNode;
            newNode->parent = closest;
        }
        if (!isBalancedTree(newNode->parent)) {
            balancingTree(newNode->parent);
        }
    }

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
                return node;
            }
            if (res < 0) {
                ans = node;
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
