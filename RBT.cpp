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
	if (node == this->root)
		return ROOT;
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

void RBT::fixAfterInsertIteration(Node * node) {
	while (node != root && getColor(node->parent) != BLACK) {
		if (getUncleColor(node) == RED) {
			setColor(node->parent, BLACK);
			setColor(node->parent->parent, RED);
			setColor(this->getUncle(node), BLACK);
			node = node->parent->parent;
		}
		else {
			Side parentSide = getSide(node->parent);

			if (getSide(node) == RIGHT && parentSide == LEFT) {
				rotateLeft(node);
				node = node->left;
			}
			else if (getSide(node) == LEFT && parentSide == RIGHT) {
				rotateRight(node);
				(node->right);
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
		else if (getSide(node) == LEFT && parentSide == RIGHT) {
			rotateRight(node);
			(node->right);
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

Node * RBT::searchPro(int value) {
	Node * ptr = this->root;
	int blackDepth = 0, depth = 0;

	while (ptr != nullptr) {

		if (getColor(ptr) == BLACK)
			blackDepth++;
		if (ptr->data == value) {
			std::cout << "Element with value " << value << ":" << std::endl;
			std::cout << "Depth: " << depth << std::endl;
			std::cout << "Black depth: " << blackDepth << std::endl;
			std::cout << "Node color: ";
			if (getColor(ptr) == BLACK)
				std::cout << "BLACK" << std::endl;
			else std::cout << "RED" << std::endl;
			return ptr;
		}
		else if (value > ptr->data)
			ptr = ptr->right;
		else ptr = ptr->left;
		depth++;
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
	std::cout << "Max depth: " << floor(2 * log2(count)) << std::endl;
}

Node * RBT::searchReplacement(Node * node) {
	if (node->left == nullptr && node->right == nullptr)
		return nullptr;

	if (node->left != nullptr) {
		node = node->left;
		while (node->right != nullptr)
			node = node->right;
		return node;
	}
	else {
		node = node->right;
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
}

void RBT::fixAfterDeletion(Node * node) {
	if (getColor(node) != DOUBLE_BLACK)
		return;

	Side side = getSide(node);
	Node * brother;

	if (side == RIGHT)
		brother = node->parent->left;
	else brother = node->parent->right;

	if (getColor(brother) == RED) {
		if (side == RIGHT)
			rotateRight(brother);
		else rotateLeft(brother);
		setColor(brother, BLACK);
		setColor(node->parent, RED);
		setColor(node, BLACK);	
		return;
	}
	else if (getColor(brother) == BLACK && getColor(brother) == BLACK) {
		setColor(brother, RED);
		setColor(node, BLACK);
		fixAfterInsert(brother);
	}
	else if ((getColor(brother->left) == RED && side == LEFT) || (getColor(brother->right) == RED && side == RIGHT)) {
		if (side == LEFT) 
			rotateRight(brother->left);
		else rotateLeft(brother->right);
		setColor(brother, RED);
		setColor(brother->parent, BLACK);
		fixAfterDeletion(node);
	}
	else {
		if (side == RIGHT) {
			rotateRight(brother);
			setColor(brother, getColor(brother->right));
		}
		else {
			rotateLeft(brother);
			setColor(brother, getColor(brother->left));
		}
		setColor(brother->left, BLACK);
		setColor(brother->right, BLACK);
	}

	setColor(this->root, BLACK);
}

void RBT::remove(int value) {
	Node * ptr = search(value);
	if (ptr == nullptr) {
		std::cout << "Element not found!" << std::endl;
		return;
	}

	Side side = getSide(ptr);
	Color removedNodeColor = getColor(ptr);
	Node * replacement = searchReplacement(ptr);

	// node with no sons
	if (replacement == nullptr) {
		// node is not root
		if (side != ROOT) {
			if (side == LEFT)
				ptr->parent->left = nullptr;
			else ptr->parent->right = nullptr;
			delete(ptr);
		}
		// node is root
		else {
			this->root = nullptr;
			delete(ptr);
			return;
		}
	}
	// node with one son
	else if ((ptr->right == nullptr) ^ (ptr->left == nullptr)){
		if (side == ROOT) {
			root = replacement;
			replacement->parent = nullptr;	
			delete(ptr);
		}
		else {
			if (side == LEFT)
				ptr->parent->left = replacement;
			else ptr->parent->right = replacement;
			replacement->parent = ptr->parent;
			delete(ptr);
		}
	}
	// node with two sons
	else {
		replacement->right = ptr->right;
		replacement->parent = ptr->parent;
		if (side != ROOT) {
			if (side == LEFT)
				ptr->parent->left = replacement;
			else ptr->parent->right = replacement;
		}
		delete(ptr);
	}

	// Check if need to repair after deletion
	if (side == ROOT) {
		setColor(this->root, BLACK);
	}
	else if (getColor(replacement) == RED) {
		setColor(replacement, BLACK);
		return;
	}
	else  if (removedNodeColor != RED){
		setColor(replacement, DOUBLE_BLACK);
		fixAfterDeletion(replacement);
	}
}

