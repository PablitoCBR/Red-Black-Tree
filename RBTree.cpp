#include <iostream>
#include "RBT.h"
#include <ctime>
#include <chrono>

int main()
{
	RBT rbt;
	//clock_t begin = clock();
	//auto start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i <= pow(10, 6); i++)
	//	rbt.add(i);
	//rbt.searchPro(555444);
	//auto finish = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> elapsed = finish - start;
	//std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	//rbt.remove(555444);
	//rbt.searchPro(555443);
	//rbt.searchPro(555445);
	//clock_t end = clock();
	//double time = double(end - begin) / CLOCKS_PER_SEC;
	//std::cout << "Czas: " << time << std::endl;

	int data;

	std::cin >> data;

	while (!std::cin.fail())
	{
		rbt.add(data);
		std::cin >> data;
	}
	std::cout << std::endl;
	rbt.printInOrder();
	rbt.printRedNodesCount();
	rbt.printActualMaxAndMinDepth();
	std::cout << std::endl;
	rbt.searchPro(9);
	std::cout << std::endl;
	rbt.remove(9);
	rbt.searchPro(22);
	std::cout << std::endl;
	rbt.printInOrder();
	rbt.printRedNodesCount();
	rbt.printActualMaxAndMinDepth();
	return 0;
}

