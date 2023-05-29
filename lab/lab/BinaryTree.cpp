#include "BinaryTree.h"

BinaryTree::BinaryTree() {
    root = nullptr;
}
BinaryTree::BinaryTree(BinaryTree& BinaryTree) {
    root = BinaryTree.root->copyNode();
}
BinaryTree::BinaryTree(int value) {
    root = new Node(value);
}
BinaryTree::BinaryTree(Node* root) {
    this->root = root;
}
BinaryTree::~BinaryTree() {
    deleteRoot();
}

Node* BinaryTree::getRoot() {
    return root;
}

void BinaryTree::deleteRoot() {
    deleteChildren(root);
    delete root;
}

void BinaryTree::deleteChildren(Node* node) {
    if (!node->getLeftNode()) {
        deleteChildren(node->getLeftNode());
    }
    if (!node->getRightNode()) {
        deleteChildren(node->getRightNode());
    }
    delete node;
}

void BinaryTree::clearTree() {
    delete root->getLeftNode();
    delete root->getRightNode();
}

bool BinaryTree::isEmpty() {
    return !(root != nullptr);
}

BinaryTree* BinaryTree::copyBinayTree(Node* node) {
    return new BinaryTree(node->copyNode());
}

int BinaryTree::getHeight() {
    return getHeight(root);
}

int BinaryTree::getHeight(Node* node, int h) {
    if (node == nullptr) {
        return h - 1;
    }
    return max(getHeight(node->getLeftNode(), h + 1), getHeight(node->getLeftNode(), h + 1));
}

int BinaryTree::getCountNodes() {
    return getCountNodes(root);
}

int BinaryTree::getCountNodes(Node* node, int c) {
    if (node == nullptr) {
        return c - 1 > 0 ? c - 1 : 0;
    }
    return getCountNodes(node->getLeftNode(), c + 1) + getCountNodes(node->getRightNode(), c + 1);
}

int BinaryTree::findMax() {
    return findMax(root);
}

int BinaryTree::findMax(Node* node) {
    if (node == nullptr) {
        return INT_MAX;
    }
    return max(node->getValue(), max(findMax(node->getLeftNode()), findMax(node->getRightNode())));
}

int BinaryTree::findMin() {
    return findMin(root);
}

int BinaryTree::findMin(Node* node) {
    if (node == nullptr) {
        return INT_MIN;
    }
    return max(node->getValue(), max(findMin(node->getLeftNode()), findMin(node->getRightNode())));
}

void BinaryTree::insert(int value) {
    insert(root, value);
}

void BinaryTree::insert(Node* node, int value) {
    if (node->getLeftNode() == nullptr) {
        node->setLeftNode(new Node(value));
        return;
    }
    if (node->getRightNode() == nullptr) {
        node->setRightNode(new Node(value));
        return;
    }
    if (rand() % 2) {
        return insert(node->getLeftNode(), value);
    }
    return insert(node->getRightNode(), value);
}

bool BinaryTree::remove(int value) {
    return remove(root, value);
}

bool BinaryTree::remove(Node* node, int value) {
    if (node == nullptr) {
        return false;
    }
    if (node->getValue() == value) {
        if (node->getLeftNode() == nullptr && node->getRightNode() == nullptr) {
            delete node;
            node = nullptr;
            return true;
        }
        if (node->getLeftNode() == nullptr) {
            Node* temp = node;
            node = node->getRightNode();
            delete temp;
            return true;
        }
        if (node->getLeftNode() == nullptr) {
            Node* temp = node;
            node = node->getLeftNode();
            delete temp;
            return true;
        }
        Node* temp = node->getLeftNode();
        while (temp->getLeftNode() != nullptr) {
            temp = temp->getLeftNode();
        }
        node->setValue(temp->getValue());
        return true;
    }
    return remove(node->getLeftNode(), value) || remove(node->getRightNode(), value);
}

bool BinaryTree::checkBalanced() {
    return checkBalanced(root);
}

bool BinaryTree::checkBalanced(Node* node) {
    if (node == nullptr) {
        return true;
    }
    if (abs(node->getLeftNode()->getNumChildren() - node->getRightNode()->getNumChildren()) > 1) {
        return false;
    }
    return checkBalanced(node->getLeftNode()) && checkBalanced(node->getRightNode());
}

int BinaryTree::getSumNodes() {
    return getSumNodes(root);
}
int BinaryTree::getSumNodes(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int sum = getSumNodes(node->getLeftNode()) + getSumNodes(node->getRightNode());
    return sum + node->getValue();
}

vector<int> BinaryTree::getAllKeysRecursive() {
    return getAllKeysRecursive(root);
}

vector<int> BinaryTree::getAllKeysRecursive(Node* node) {
    vector<int> keys;
    if (node->getLeftNode() != nullptr) {
        vector<int> leftKeys = getAllKeysRecursive(node->getLeftNode());
        keys.insert(keys.end(), leftKeys.begin(), leftKeys.end());
    }
    keys.push_back(node->getValue());
    if (node->getRightNode() != nullptr) {
        vector<int> rightKeys = getAllKeysRecursive(node->getRightNode());
        keys.insert(keys.end(), rightKeys.begin(), rightKeys.end());
    }
    return keys;
}

void BinaryTree::outputTree() {
    outputTree(root);
}

void BinaryTree::outputTree(Node* node, int depth) {
    if (node == nullptr) {
        return;
    }
    outputTree(node->getRightNode(), depth + 1);
    cout << string(4 * depth, ' ') << node->getValue() << endl;
    outputTree(node->getLeftNode(), depth + 1);
}

void BinaryTree::printLevel(Node* node, int level, int index) {
    if (node == nullptr) {
        return;
    }
    if (level == 0) {
        std::cout << node->getValue() << " ";
    }
    else {
        printLevel(node->getLeftNode(), level - 1, 2 * index);
        printLevel(node->getRightNode(), level - 1, 2 * index + 1);
    }
    if (index == (1 << level) - 1) {
        std::cout << std::endl;
    }
}

void BinaryTree::printTreeLevels(Node* node) {
    int height = getHeight(node);
    for (int i = 0; i <= height; i++) {
        printLevel(node, i, 0);
    }
}

void BinaryTree::printLeaves(Node* node) {
    if (node == nullptr) {
        return;
    }
    if (node->getLeftNode() == nullptr && node->getRightNode() == nullptr) {
        std::cout << node->getValue() << " ";
    }
    printLeaves(node->getLeftNode());
    printLeaves(node->getRightNode());
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this == &other) {
        return *this;
    }
    this->clearTree();
    root->setValue(other.root->getValue());
    root->setLeftNode(other.root->getLeftNode()->copyNode());
    root->setRightNode(other.root->getRightNode()->copyNode());
    return *this;
}

const Node* BinaryTree::getRoot() const {
    return root;
}


int BinaryTree::getLevel(int key) {
    return getLevel(root, key);
}

int BinaryTree::getLevel(Node* node, int key) {
    if (node == nullptr) {
        return -1;
    }
    if (node->getValue() == key) {
        return 0;
    }
    int leftLevel = getLevel(node->getLeftNode(), key);
    if (leftLevel != -1) {
        return leftLevel + 1;
    }
    int rightLevel = getLevel(node->getRightNode(), key);
    if (rightLevel != -1) {
        return rightLevel + 1;
    }
    return -1;
}
