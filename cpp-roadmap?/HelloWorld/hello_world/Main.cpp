#include <iostream>

using namespace std;

double square_area (double width, double height)
{
	return width*height;
}

bool get_answer ()
{
	char answer = 0;
	cin >> answer;
	if (answer == 'y') return true;
	return false;
}

int main ()
{
	cout << "Square 10x200 = " << square_area(10, 200) << endl;
	cout << "Hola, Mundo!" << endl;
	cout << "sizeof(bool) = " << sizeof(bool) << endl;
	cout << "sizeof(char) = " << sizeof(char) << endl;
	cout << "sizeof(int)= " << sizeof(int) << endl;
	cout << "sizeof(double) = " << sizeof(double) << endl;
	int n = 200;
	int *p = &n;
	cout << *p << endl;
	return 0;
}


