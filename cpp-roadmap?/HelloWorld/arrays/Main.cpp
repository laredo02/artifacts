#include <iostream>

int foo [] = {0, 1, 2, 3, 4};

int arr () {
	int foo [] = {4, 3, 2, 1, 0};
	for (int i: foo) {
		std::cout << i;
	}
	std::cout << std::endl;
	for (int i: ::foo) {
		std::cout << i;
	}
	std::cout << std::endl;
}

int main ()
{
	arr();
	return 0;
}
