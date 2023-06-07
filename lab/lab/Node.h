#pragma once
class Node {
public:
    Node(int value = 0);
    Node(int value, Node* leftNode, Node* rightNode);
    Node* getLeftNode();
    void setLeftNode(Node* leftNode);
    Node* getRightNode();
    void setRightNode(Node* rightNode);
    int getValue();
    void setValue(int value);
    int getNumChildren();
    Node* copyNode();
    Node* copyNode(Node* node);
private:
    Node* leftNode;
    Node* rightNode;
    int value;
};

