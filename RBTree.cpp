#include <iostream>
#include "RBT.h"

int main()
{
	RBT rbt;
	int data;

	std::cin >> data;

	while (data != 0)
	{
		rbt.add(data);
		std::cin >> data;
	}

	rbt.printInOrder();
	rbt.printRedNodesCount();
	rbt.printActualMaxAndMinDepth();
	return 0;
}

