#include "Node.h"

    Node::Node(int value) {
        this->value = value;
        leftNode = nullptr;
        rightNode = nullptr;
    }
    Node::Node(int value, Node* leftNode, Node* rightNode) {
        this->value = value;
        this->leftNode = leftNode;
        this->rightNode = rightNode;
    }
    Node* Node::getLeftNode() {
        return leftNode;
    }
    void Node::setLeftNode(Node* leftNode) {
        this->leftNode = leftNode;
    }
    Node* Node::getRightNode() {
        return rightNode;
    }
    void Node::setRightNode(Node* rightNode) {
        this->rightNode = rightNode;
    }
    int Node::getValue() {
        return value;
    }
    void Node::setValue(int value) {
        this->value = value;
    }
    int Node::getNumChildren() {
        return (leftNode != nullptr) + (rightNode != nullptr);
    }
    Node* Node::copyNode() {
        Node* newNode = new Node(this->value);
        if (this->getLeftNode() != nullptr) {
            newNode->leftNode = copyNode(this->getLeftNode());
        }
        if (this->getRightNode() != nullptr) {
            newNode->rightNode = copyNode(this->getRightNode());
        }
        return newNode;
    }
    Node* Node::copyNode(Node* node) {
        Node* newNode = new Node(this->value);
        if (node->leftNode != nullptr) {
            newNode->leftNode = copyNode(node->leftNode);
        }
        if (node->rightNode != nullptr) {
            newNode->rightNode = copyNode(node->rightNode);
        }
        return newNode;
    }
