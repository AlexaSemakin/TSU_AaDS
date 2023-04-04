#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include <cassert>

using namespace std;

class BinaryTree{
public:
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
        void setLeftNode(Node* leftNode){
            this->leftNode = leftNode;
        }
        Node* getRightNode(){
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
        Node* copyNode(){
            Node* newNode = new Node(this->value);
            if (this->getLeftNode() != nullptr){
                newNode->leftNode = copyNode(this->getLeftNode());
            }
            if (this->getRightNode() != nullptr){
                newNode->rightNode = copyNode(this->getRightNode());
            }
            return newNode;
        }
        Node* copyNode(Node* node){
            Node* newNode = new Node(this->value);
            if (node->leftNode != nullptr){
                newNode->leftNode = copyNode(node->leftNode);
            }
            if (node->rightNode != nullptr){
                newNode->rightNode = copyNode(node->rightNode);
            }
            return newNode;
        }
    private:
        Node* leftNode;
        Node* rightNode;
        int value;
    };
    
    BinaryTree(){
        root = nullptr;
    }
    BinaryTree(BinaryTree& BinaryTree){
        root = BinaryTree.root->copyNode();
    }
    BinaryTree(int value){
        root = new Node(value);
    }
    BinaryTree(Node* root){
        this->root = root;
    }
    ~BinaryTree(){
        deleteRoot();
    }
    
    Node* getRoot(){
        return root;
    }
    
    void deleteRoot(){
        deleteChildren(root);
        delete root;
    }
    
    void deleteChildren(Node* node){
       if (!node->getLeftNode()){
           deleteChildren(node->getLeftNode());
       }
        if (!node->getRightNode()){
           deleteChildren(node->getRightNode());
       }
       delete node;
   }
    
    void clearTree(){
        delete root->getLeftNode();
        delete root->getRightNode();
    }

    bool isEmpty(){
        return !(root!=nullptr);
    }

    BinaryTree* copyBinayTree(Node* node){
        return new BinaryTree(node->copyNode());
    }

    int getHeight(){
        return getHeight(root);
    }

    int getHeight(Node* node, int h = 0){
        if (node == nullptr){
            return h-1;
        }
        return max(getHeight(node->getLeftNode(), h+1), getHeight(node->getLeftNode(), h+1));
    }

    int getCountNodes(){
        return getCountNodes(root);
    }

    int getCountNodes(Node* node, int c = 0){
        if (node == nullptr){
            return c-1 > 0 ? c - 1 : 0;
        }
        return getCountNodes(node->getLeftNode(), c+1) + getCountNodes(node->getRightNode(), c+1);
    }
    
    int findMax() {
        return findMax(root);
    }

    int findMax(Node* node) {
        if (node== nullptr){
            return INT_MAX;
        }
        return max(node->getValue(), max(findMax(node->getLeftNode()), findMax(node->getRightNode())));
    }

    int findMin() {
        return findMin(root);
    }

    int findMin(Node* node) {
        if (node== nullptr){
            return INT_MIN;
        }
        return max(node->getValue(), max(findMin(node->getLeftNode()), findMin(node->getRightNode())));
    }
     
    void insert(int value){
        insert(root, value);
    }

    void insert(Node* node, int value) {
        if (node->getLeftNode() == nullptr){
            node->setLeftNode(new Node(value));
            return;
        }
        if (node->getRightNode() == nullptr){
            node->setRightNode(new Node(value));
            return;
        }
        if (rand()%2){
            return insert(node->getLeftNode(), value);
        }
        return insert(node->getRightNode(), value);
    }
    
    bool remove(int value){
        return remove(root, value);
    }

    bool remove(Node* node, int value) {
        if (node == nullptr){
            return false;
        }
        if (node->getValue() == value){
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
    
    bool checkBalanced(){
        return checkBalanced(root);
    }

    bool checkBalanced(Node* node){
        if (node == nullptr){
            return true;
        }
        if (abs(node->getLeftNode()->getNumChildren() - node->getRightNode()->getNumChildren())>1){
            return false;
        }
        return checkBalanced(node->getLeftNode()) && checkBalanced(node->getRightNode());
    }
    
    int getSumNodes(){
        return getSumNodes(root);
    }
    int getSumNodes(Node* node){
        if (node == nullptr){
            return 0;
        }
        int sum = getSumNodes(node->getLeftNode()) + getSumNodes(node->getRightNode());
        return sum + node->getValue();
    }
    
    vector<int> getAllKeysRecursive(){
        return getAllKeysRecursive(root);
    }

    vector<int> getAllKeysRecursive(Node* node) {
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

    void outputTree(){
        outputTree(root);
    }

    void outputTree(Node* node, int depth = 0) {
        if (node == nullptr) {
            return;
        }
        outputTree(node->getRightNode(), depth + 1);
        cout << string(4 * depth, ' ') << node->getValue() << endl;
        outputTree(node->getLeftNode(), depth + 1);
    }

    void printLevel(Node* node, int level, int index) {
        if (node == nullptr) {
            return;
        }
        if (level == 0) {
            std::cout << node->getValue() << " ";
        } else {
            printLevel(node->getLeftNode(), level - 1, 2 * index);
            printLevel(node->getRightNode(), level - 1, 2 * index + 1);
        }
        if (index == (1 << level) - 1) {
            std::cout << std::endl;
        }
    }

    void printTreeLevels(Node* node) {
        int height = getHeight(node);
        for (int i = 0; i <= height; i++) {
            printLevel(node, i, 0);
        }
    }

    void printLeaves(Node* node) {
        if (node == nullptr) {
            return;
        }
        if (node->getLeftNode() == nullptr && node->getRightNode() == nullptr) {
            std::cout << node->getValue() << " ";
        }
        printLeaves(node->getLeftNode());
        printLeaves(node->getRightNode());
    }
    
    BinaryTree& operator=(const BinaryTree& other) {
        if (this == &other) {
            return *this;
        }
        this->clearTree();
        root->setValue(other.root->getValue());
        root->setLeftNode(other.root->getLeftNode()->copyNode());
        root->setRightNode(other.root->getRightNode()->copyNode());
        return *this;
    }

    const Node* getRoot() const{
        return root;
    }
    
    
    int getLevel(int key){
        return getLevel(root, key);
    }

    int getLevel(Node* node, int key) {
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
    
    protected:
        Node* root;
};


class SearchBinaryTree:BinaryTree{
    
    int findMax() {
        return findMax(root);
    }

    int findMax(Node* node) {
        if (node->getRightNode() == nullptr) {
            return node->getValue();
        }
        return findMax(node->getRightNode());
    }

    int findMin() {
        return findMin(root);
    }

    int findMin(Node* node) {
        if (node->getLeftNode() == nullptr) {
            return node->getValue();
        }
        return findMin(node->getLeftNode());
    }
     
    void insert(int value){
        insert(root, value);
    }

    void insert(Node* node, int value) {
        if (node == nullptr) {
            node = new Node(value);
            return;
        }
        if (value <= node->getValue()) {
            if (node->getLeftNode() == nullptr) {
                node->setLeftNode(new Node(value));
                return;
            }
            insert(node->getLeftNode(), value);
        }
        else {
            if (node->getRightNode() == nullptr) {
                node->setRightNode(new Node(value));
                return;
            }
            insert(node->getRightNode(), value);
        }
    }

    bool remove(int value){
        return remove(root, value);
    }

    bool remove(Node* node, int value) {
       if (node == nullptr) {
           return false;
       }
       if (value < node->getValue()) {
           return remove(node->getLeftNode(), value);
       }
       if (value > node->getValue()) {
           return remove(node->getRightNode(), value);
       }
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
        
    Node* getNode(int val){
        return getNode(root, val);
    }
    Node* getNode(Node* node, int val){
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->getValue() == val){
            return node;
        }
        if (node->getValue() <= val){
            return getNode(node->getLeftNode(), val);
        }
        return getNode(node->getRightNode(), val);
    }
    
    int getLevel(int val){
        return getLevel(root, val);
    }
    
    int getLevel(Node* node, int val) {
        if (node == nullptr) {
            return -1;
        }
        if (node->getValue() == val) {
            return 0;
        }
        if (val <= node->getValue())
        {
            int leftLevel = getLevel(node->getLeftNode(), val);
            if (leftLevel != -1) {
                return leftLevel + 1;
            }
            return -1;
        }
        int rightLevel = getLevel(node->getRightNode(), val);
        if (rightLevel != -1) {
            return rightLevel + 1;
        }
        return -1;
    }
    
};

int main(){
    return 0;
}
