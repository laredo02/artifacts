#include <iostream>

using namespace std;

extern "C" void printLine(char strp, int len)
{
	for(int i=strp; i<strp+len*sizeof(char); i+=sizeof(char)) {
		cout << i << endl;
	}
}

