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
        if (!root->getLeftNode()){
            deleteChildren(root->getLeftNode());
        }
        if (!root->getRightNode()){
            deleteChildren(root->getRightNode());
        }
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
       return remove(node->getRightNode(), temp->getValue());
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

    private:
        Node* root;
};

class BinaryTreeTester
{
public:
    BinaryTreeTester() = default;
    ~BinaryTreeTester() = default;
    
    void test(const int size);

protected:
    void check_addAndCount(const BinaryTree &tree, const int size);
    void check_remove(const BinaryTree &tree, const int size);
    //ToDo: check_clear()
    //ToDo: check_assign()
    void check_height(const BinaryTree &tree, const int size);

private:
    void addAndCount();
    void destructor();
    void remove();
    void clear(); //ToDo: реализовать
    void assign(); //ToDo: переделать из функции
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees();
    
private:
    int m_maxSize;
};

//ToDo: переместить реализации методов в отдельный .cpp

void BinaryTreeTester::test(const int size)
{
    m_maxSize = size;
    addAndCount();
    destructor();
    remove();
    clear();
    assign();
    height();
}

void BinaryTreeTester::addAndCount()
{
    BinaryTree tree;
    check_addAndCount(tree, 0);
    
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree.insert(i);
        check_addAndCount(tree, i + 1);
    }
}

void BinaryTreeTester::check_addAndCount(const BinaryTree &tree, const int size)
{
    assert(tree.getCountNodes() == size);
}

void BinaryTreeTester::destructor()
{
    //ToDo: цикл + wait
    {
        BinaryTree tree;
        for (int i = 0 ; i < m_maxSize; ++i) {
            tree.insert(i);
        }
    }
}

void BinaryTreeTester::remove()
{
    int invalidKey = -1;
    std::vector<int> nodeKeys;

    BinaryTree tree;
    tree.remove(invalidKey);
    
    for (int i = 0 ; i < m_maxSize; ++i) {
        nodeKeys.push_back(i);
        tree.insert(i);
    }

    while (!nodeKeys.empty()) {
        int removedNodeIndex = rand() % nodeKeys.size(); //3
        
        tree.remove(invalidKey);
        check_remove(tree, nodeKeys.size());

        tree.remove(removedNodeIndex);
        nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);
        check_remove(tree, nodeKeys.size());

        //ToDo: вывести дерево для визуальной проверки удаления и вывода
    }

    //ToDo: вывести дерево для визуальной проверки удаления и вывода
    tree.remove(invalidKey);
    check_remove(tree, nodeKeys.size());
}

void BinaryTreeTester::check_remove(const BinaryTree &tree, const int size)
{
    assert(tree.getCountNodes() == size);
}

//ToDo: переделать остальные функции в методы класса и вынести проверки

void BinaryTreeTester::height()
{
    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

void BinaryTreeTester::check_height(const BinaryTree &tree, const int height)
{
    assert(tree.getHeight() == height);
}

void BinaryTreeTester::height_trivialCases()
{
    BinaryTree tree;
    check_height(tree, 0);
    tree.insert(0);
    check_height(tree, 1);
}

void BinaryTreeTester::height_longOnlyLeftSubtree()
{
    BinaryTree longTree;
    longTree.insert(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setLeftNode(new BinaryTree::Node(i));
        runner = runner->getLeftNode();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyRightSubtree()
{
    BinaryTree longTree;
    longTree.insert(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setRightNode(new BinaryTree::Node(i));
        runner = runner->getRightNode();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees()
{
    BinaryTree longTree;
    longTree.insert(0);
    BinaryTree::Node *leftRunner = longTree.getRoot();
    BinaryTree::Node *rightRunner = longTree.getRoot();
    for (int i = 1; i < m_maxSize/2; ++i) {
        leftRunner->setLeftNode(new BinaryTree::Node(i));
        leftRunner = leftRunner->getLeftNode();
        check_height(longTree, i + 1);
        

        rightRunner->setRightNode(new BinaryTree::Node(i));
        rightRunner = rightRunner->getRightNode();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longRandomZigzagSubtrees()
{
    BinaryTree longTree;
    longTree.insert(0);
    BinaryTree::Node *leftRunner = longTree.getRoot();
    BinaryTree::Node *rightRunner = longTree.getRoot();

    leftRunner->setLeftNode(new BinaryTree::Node(1));
    leftRunner = leftRunner->getLeftNode();
    rightRunner->setLeftNode(new BinaryTree::Node(1));
    rightRunner = rightRunner->getLeftNode();

    for (int i = 2; i < m_maxSize/2; ++i) {
        if (rand() % 2 == 0) 
        {
            leftRunner->setLeftNode(new BinaryTree::Node(i));
            leftRunner = leftRunner->getLeftNode();
        }
        else 
        {
            leftRunner->setRightNode(new BinaryTree::Node(i));
            leftRunner = leftRunner->getLeftNode(); 
        }
        check_height(longTree, i + 1);

        if (rand() % 2 == 0)
        {
            rightRunner->setLeftNode(new BinaryTree::Node(i));
            rightRunner = rightRunner->getLeftNode();
        }
        else 
        {
            rightRunner->setRightNode(new BinaryTree::Node(i));
            rightRunner = rightRunner->getLeftNode(); 
        }
        check_height(longTree, i + 1);
    }
}



int main(){

}