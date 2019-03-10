#include "RBT.h"
#include <iostream>
#include <cmath>

Node::Node(int value) {
	this->data = value;
	this->color = RED;
	this->left = this->right = this->parent = nullptr;
}

Color RBT::getColor(Node * node) {
	if (node == nullptr)
		return BLACK;
	else return node->color;
}

void RBT::setColor(Node * node, Color color) {
	node->color = color;
}

Side RBT::getSide(Node * node) {
	if (node->parent->left == node)
		return LEFT;
	else return RIGHT;
}

Node * RBT::getUncle(Node * node) {
	if (getSide(node->parent) == LEFT)
		return node->parent->parent->right;
	else return node->parent->parent->left;
}

Color RBT::getUncleColor(Node * node) {
	if (getUncle(node) == nullptr)
		return BLACK;
	else return getUncle(node)->color;
}

void RBT::rotateLeft(Node * node) {
	Node * parent = node->parent;
	Node * leftChild = node->left;
	Node * grandparent = parent->parent;

	if (this->root == parent)
		this->root = node;

	node->parent = grandparent;
	node->left = parent;
	
	if (grandparent != nullptr) {
		if (getSide(parent) == LEFT)
			grandparent->left = node;
		else grandparent->right = node;
	}

	parent->parent = node;
	parent->right = leftChild;
}

void RBT::rotateRight(Node * node) {
	Node * parent = node->parent;
	Node * rightChild = node->right;
	Node * grandparent = parent->parent;

	if (this->root == parent)
		this->root = node;

	node->parent = grandparent;
	node->right = parent;

	if (grandparent != nullptr) {
		if (getSide(parent) == LEFT)
			grandparent->left = node;
		else grandparent->right = node;
	}

	parent->parent = node;
	parent->left = rightChild;
}

void RBT::fixAfterInsert(Node * node) {
	if (node == this->root)
		return;
	
	if (getColor(node->parent) == BLACK)
		return;

	if (getUncleColor(node) == RED) {
		setColor(node->parent, BLACK);
		setColor(node->parent->parent, RED);
		setColor(this->getUncle(node), BLACK);
		fixAfterInsert(node->parent->parent);
	}
	else {
		Side parentSide = getSide(node->parent);

		if (getSide(node) == RIGHT && parentSide == LEFT) {
			rotateLeft(node);
			fixAfterInsert(node->left);
		}
		else if (getSide(node) == LEFT && parentSide == RIGHT){
			rotateRight(node);
			fixAfterInsert(node->right);
		}
		else {
			if (parentSide == LEFT) {
				rotateRight(node->parent);
				setColor(node->parent, BLACK);
				setColor(node->parent->right, RED);
			}
			else {
				rotateLeft(node->parent);
				setColor(node->parent, BLACK);
				setColor(node->parent->left, RED);
			}	
		}
	}
	setColor(this->root, BLACK);
}

void RBT::add(int value) {
	Node * newNode = new Node(value);
	Node *ptr = root, *parent = root;

	if (root == nullptr) {
		setColor(newNode, BLACK);
		root = newNode;
		return;
	}

	while (ptr != nullptr) {
		parent = ptr;
		if (ptr->data <= value)
			ptr = ptr->right;
		else ptr = ptr->left;
	}

	newNode->parent = parent;
	
	if (parent->data <= value)
		parent->right = newNode;
	else parent->left = newNode;

	if (getColor(parent) == BLACK)
		return;
	else fixAfterInsert(newNode);
}

Node * RBT::search(int value) {
	Node * ptr = root;
	while (ptr != nullptr) {
		if (ptr->data == value)
			return ptr;
		else if (value > ptr->data)
			ptr = ptr->right;
		else ptr = ptr->left;
	}
	return nullptr;
}

void RBT::inOrder(Node * node) {
	if (node != nullptr) {
		inOrder(node->left);
		std::cout << node->data << " ";
		inOrder(node->right);
	}
}

void RBT::printInOrder() {
	inOrder(this->root);
}

void RBT::countRedNodes(Node * node, int * count) {
	if (node != nullptr) {
		countRedNodes(node->left, count);
		if (getColor(node) == RED)
			(*count)++;
		countRedNodes(node->right, count);
	}
}

void RBT::printRedNodesCount() {
	int count = 0;
	countRedNodes(this->root, &count);
	std::cout << std::endl << "Red nodes: " << count << std::endl;
}

void RBT::countNodes(Node * node, int * count) {
	if (node != nullptr) {
		countNodes(node->left, count);
		(*count)++;
		countNodes(node->right, count);
	}
}

void RBT::printActualMaxAndMinDepth() {
	int count = 0;
	countNodes(root, &count);
	std::cout << "Min depth: " << ceil(log2(count)) << std::endl;
	std::cout << "Max depth: " << ceil(2*log2(count)) << std::endl;
}