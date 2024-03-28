#include <iostream>

int main ()
{
	int arr [10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int *p0 = &arr[0];
	int *p10 = &arr[10];

	std::cout << (int)p0 << std::endl;
	std::cout << (int)p10 << std::endl;
	std::cout << "sizeof = " << sizeof(int) << "\tp10 - p0 = " << p10 - p0 <<  std::endl << std::endl;

	int *arrp = &arr[0];

	for (int i=0; i<10; i++) {
		std::cout << (int)arrp << " = " << *arrp << std::endl;
		arrp++;
	}

}

