#include <iostream>
#include <string>

class Tree;
class TreeIterator;

class Node {
private:
    Node *left, *right, *parent;
    friend class Tree;
    friend class TreeIterator;

public:
    Node* getLeft() { return left; }
    const Node* getLeft() const { return left; }
    Node* getRight() { return right; }
    const Node* getRight() const { return right; }
    Node* getParent() { return parent; }
    const Node* getParent() const { return parent; }

    std::string name;

    Node() : name(""), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(const std::string& _name, Node* _parent = nullptr)  
        : name(_name), left(nullptr), right(nullptr), parent(_parent) {}

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

class TreeIterator: public std::iterator<std::input_iterator_tag, Node> {
private:
    Node* node;
public:
    TreeIterator() : node(nullptr) {}
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
        }
        a->right = b->left;
        b->left = a;
    }

    void smallTurnRight(Node* a, Node* b) {
        if (a->parent) {
            a->parent->left = b;
        }
        b->parent = a->parent;
        a->parent = b;
        if (b->right) {
            b->right->parent = a;
        }
        a->left = b->right;
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

    Tree() : root(nullptr) {}

    int getHeight(const Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int left = getHeight(node->left);
        int right = getHeight(node->right);
        return std::max(left, right) + 1;
    }

    Node* findUnbalanced(Node* node) {
        int left, right;
        while (node) {
            left = getHeight(node->left);
            right = getHeight(node->right);
            if (abs(left - right) >= 2) {
                return node;  
            }
            node = node->parent;
        }
        return nullptr;
    }
    
    void balancingTree(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right); 
        Node* newRoot = root;
        if (leftHeight > rightHeight) {
            Node* child = node->left;
            leftHeight = getHeight(child->left);
            rightHeight = getHeight(child->right);
            if (leftHeight >= rightHeight) {
                smallTurnRight(node, child);
            }
            else {
                bigTurnLeft(node, child, child->right);
            }
        }
        else {
            Node* child = node->right;
            leftHeight = getHeight(child->left);
            rightHeight = getHeight(child->right);
            if (leftHeight <= rightHeight) {
                smallTurnLeft(node, child);
            }
            else {
                bigTurnRight(node, child, child->left);
            }
        }
        if (node == root) {
            root = node->parent;
        }
    }

    Node* addNode(const std::string& name) {
        Node* closest = findClosest(name);
        if (closest && closest->name == name) {
            return nullptr;
        }
        Node* newNode = new Node(name, closest);
        if (closest == nullptr) {
            Node* maxNode = findMax();
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
            newNode->left = closest->left;
            closest->left = newNode;
            newNode->parent = closest;
        }
        Node* unbalanced = findUnbalanced(newNode->parent);
        if (unbalanced != nullptr) {
            balancingTree(unbalanced);
        }

        return newNode;
    }

    Node* findNode(const std::string& name) {
        for (auto node = root; node;) {
            auto res = name.compare(node->name);
            if (res == 0) {
                return node;
            }
            else if (res < 0) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return nullptr;
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
        
        Node* closest = node->right;
        if (closestMin) {
            closest = closestMin;

            // changing node to be deleted to max node in left subtree
            closestMin->right = node->right;
            closestMin->left = nullptr;
            if (closestMin->parent != node) {
                // if closestMin has subtree
                closestMin->parent->right = closestMin->left; 
                if (closestMin->left) {
                    closestMin->left->parent = closestMin->parent;
                }
                closestMin->left = node->left;
                node->left->parent = closestMin;
            }
            closestMin->parent = node->parent;
        }
        if (node->right) {
            if (closestMin) {
                node->right->parent = closestMin;
            }
            else {
                node->right->parent = node->parent;
            }
        }

        Node* parent = node->parent;
        if (parent) {
            // find where is node (left or right subtree)
            auto compareWithParent = node->name.compare(parent->name);
            if (compareWithParent < 0) {
                parent->left = closest;
            }
            else {
                parent->right = closest;
            }
        }
        if (node == root) {
            root = closest;
        }
        delete node;
        Node* balanceFrom = parent;
        if (closest) {
            balanceFrom = closest;
        }
        if (balanceFrom) {
            Node* unbalanced = findUnbalanced(balanceFrom);
            if (unbalanced != nullptr) {
                balancingTree(unbalanced);
            }
        }
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
    
    TreeIterator begin() {
        return TreeIterator(findMin());
    }
    TreeIterator end() {
        return TreeIterator();
    }
};
 
int main() {
    Tree bst;
    for (int i = 0; i < 5; i++) {
        bst.addNode(std::to_string(i));
    }

    for (auto it = bst.begin(); it != bst.end(); it++) {
        Node newNode = *it;
        std::cout << "Hello, I am " << newNode.name << std::endl;
        if (newNode.getParent())
            std::cout << "parent " << newNode.getParent()->name << std::endl;
        if (newNode.getLeft())
            std::cout << "left " << newNode.getLeft()->name << std::endl;
        if (newNode.getRight())
            std::cout << "right " << newNode.getRight()->name << std::endl;
        std::cout << std::endl;
    }
    Node* nodeToDelete = bst.findNode("3");
    std::cout << "Delete " << nodeToDelete->name << std::endl;
    bst.deleteNode(nodeToDelete);
    for (auto it = bst.begin(); it != bst.end(); it++) {
        Node newNode = *it;
        std::cout << "Hello, I am " << newNode.name << std::endl;
        if (newNode.getParent())
            std::cout << "parent " << newNode.getParent()->name << std::endl;
        if (newNode.getLeft())
            std::cout << "left " << newNode.getLeft()->name << std::endl;
        if (newNode.getRight())
            std::cout << "right " << newNode.getRight()->name << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
