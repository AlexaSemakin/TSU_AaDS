#pragma once
#include "BinaryTree.h"
class SearchBinaryTree :
	public BinaryTree
{
	int findMax();

	int findMax(Node* node);

	int findMin();

	int findMin(Node* node);

	void insert(int value);

	void insert(Node* node, int value);

	bool remove(int value);

	bool remove(Node* node, int value);

	Node* getNode(int val);

	Node* getNode(Node* node, int val);

	int getLevel(int val);

	int getLevel(Node* node, int val);
};

