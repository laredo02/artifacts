
#include <iostream>
#include <string>

using namespace std;

string toLowerCase(string s) {
	for (int i=0; i<s.size(); i++) {
		char c = s[i];
		if ('A' <= c && c <= 'Z') {
			s[i] = ('a' + (c - 'A'));
		}
	}	
	return s;	
}


int main (){

	std::cout << toLowerCase("Hola Mundo") << std::endl;

	return 0;
}



