#include <iostream>
#include "RBT.h"
#include <ctime>
#include <chrono>

int main()
{
	RBT rbt;
	//clock_t begin = clock();
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i <= pow(10, 6); i++)
		rbt.add(i);
	rbt.searchPro(555444);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	//clock_t end = clock();
	//double time = double(end - begin) / CLOCKS_PER_SEC;
	//std::cout << "Czas: " << time << std::endl;

	//int data;

	//std::cin >> data;

	//while (data != 0)
	//{
	//	rbt.add(data);
	//	std::cin >> data;
	//}

	//rbt.printInOrder();
	//rbt.printRedNodesCount();
	//rbt.printActualMaxAndMinDepth();
	//rbt.searchPro(9);
	return 0;
}

