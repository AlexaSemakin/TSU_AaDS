#include <iostream>

class Node{
    public:
        Node(int value = 0){
            this->value = value;
            leftNode = nullptr;
            rightNode = nullptr;
        }

        Node(int value, Node* leftNode, Node* rightNode){
            this->value = value;
            this->leftNode = leftNode;
            this->rightNode = rightNode;
        }

        Node* getLeftNode(){
            return leftNode;
        }
        
        void settLeftNode(Node* leftNode){
            this->leftNode = leftNode;
        }

        Node* getRrightNode(){
            return rightNode;
        }

        void setRightNode(Node* rightNode){
            this->rightNode = rightNode;
        }

        int getValue(){
            return value;
        }

        void setValue(int value){
            this->value = value;
        }

        int getNumChildren(){
            return (leftNode != nullptr) + (rightNode != nullptr);
        }
    private:
        Node* leftNode;
        Node* rightNode;
        int value;
};