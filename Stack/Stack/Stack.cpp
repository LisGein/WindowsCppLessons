// Stask.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>

class Func{
public:
	void Enter(){
		int mass[10];
		for (int i = 1; i < 11; i++){
			std::cout << "Enter the " << i << " element of the array" << std::endl;
			std::cin >> mass[i];
		}
	}

};


int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Hello world!" << std::endl;
	return 0;
}
