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
	void fixAfterInsertIteration(Node *);
	Node * getUncle(Node *);
	Color getUncleColor(Node *);
	void inOrder(Node *);
	void countRedNodes(Node *, int *);
	void countNodes(Node *, int *);
	void fixAfterDeletion(Node *);
	Node * searchReplacement(Node *); // search for replacement after deletion (priority left)
public:
	void add(int);
	Node * search(int);
	Node * searchPro(int); // search for value and prints it depth and black depth and node color
	void printInOrder();
	void printRedNodesCount();
	void printActualMaxAndMinDepth();
	void remove(int);
};