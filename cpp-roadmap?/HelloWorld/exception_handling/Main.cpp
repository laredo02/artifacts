#include <iostream>

int division(int x, int y);

int main ()
{
	division(100, 0);
	std::cout << "100 / 2 = " << division(100, 2) << std::endl;
}

int division (int x, int y)
{
	try {
		if (y==0) {
			throw y;
		} else {
			return x/y;
		}
	} catch (int e) {
		std::cout << "Exception found -----> division by " << e << std::endl;
	}
}
