#include "SearchBinaryTree.h"


int SearchBinaryTree::findMax() {
	return findMax(root);
}

int SearchBinaryTree::findMax(Node* node) {
	if (node->getRightNode() == nullptr) {
		return node->getValue();
	}
	return findMax(node->getRightNode());
}

int SearchBinaryTree::findMin() {
	return findMin(root);
}

int SearchBinaryTree::findMin(Node* node) {
	if (node->getLeftNode() == nullptr) {
		return node->getValue();
	}
	return findMin(node->getLeftNode());
}

void SearchBinaryTree::insert(int value) {
	insert(root, value);
}

void SearchBinaryTree::insert(Node* node, int value) {
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

bool SearchBinaryTree::remove(int value) {
	return remove(root, value);
}

bool SearchBinaryTree::remove(Node* node, int value) {
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

Node* SearchBinaryTree::getNode(int val) {
	return getNode(root, val);
}

Node* SearchBinaryTree::getNode(Node* node, int val) {
	if (node == nullptr)
	{
		return nullptr;
	}
	if (node->getValue() == val) {
		return node;
	}
	if (node->getValue() <= val) {
		return getNode(node->getLeftNode(), val);
	}
	return getNode(node->getRightNode(), val);
}

int SearchBinaryTree::getLevel(int val) {
	return getLevel(root, val);
}

int SearchBinaryTree::getLevel(Node* node, int val) {
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
