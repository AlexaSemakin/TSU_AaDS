#pragma once
#include "Node.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
using std::min;
using std::max;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

class BinaryTree {
public:
	BinaryTree();
	BinaryTree(BinaryTree& BinaryTree);
	BinaryTree(int value);
	BinaryTree(Node* root);
	~BinaryTree();

	const Node* getRoot() const;

	void deleteRoot();

	void deleteChildren(Node* node);

	void clearTree();

	bool isEmpty();
	BinaryTree* copyBinayTree(Node* node);
	int getHeight();

	int getHeight(Node* node, int h = 0);

	int getCountNodes();

	int getCountNodes(Node* node, int c = 0);

	int findMax();

	int findMax(Node* node);

	int findMin();

	int findMin(Node* node);

	void insert(int value);

	void insert(Node* node, int value);

	bool remove(int value);

	bool remove(Node* node, int value);

	bool checkBalanced();

	bool checkBalanced(Node* node);

	int getSumNodes();
	int getSumNodes(Node* node);

	std::vector<int> getAllKeysRecursive();

	std::vector<int> getAllKeysRecursive(Node* node);

	void outputTree();

	void outputTree(Node* node, int depth = 0);

	void printLevel(Node* node, int level, int index);

	void printTreeLevels(Node* node);

	void printLeaves(Node* node);

	BinaryTree& operator=(const BinaryTree& other);

	Node* getRoot();

	int getLevel(int key);

	int getLevel(Node* node, int key);

protected:
	Node* root;
};