#pragma once

enum Color {RED, BLACK};
enum Side {LEFT, RIGHT};

struct Node {
	int data;
	Color color;
	Node *parent, *right, *left;

	Node(int);
};

class RBT {
private:
	Node * root = nullptr;
protected:
	void rotateLeft(Node *);
	void rotateRight(Node *);
	void setColor(Node *, Color);
	Color getColor(Node *);
	Side getSide(Node *); // check if node is right or left son of his parent
	void fixAfterInsert(Node *);
	Node * getUncle(Node *);
	Color getUncleColor(Node *);
	void inOrder(Node *);
	void countRedNodes(Node *, int *);
	void countNodes(Node *, int *);
public:
	void add(int);
	Node * search(int);
	void printInOrder();
	void printRedNodesCount();
	void printActualMaxAndMinDepth();
};