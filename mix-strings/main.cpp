
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string mergeAlternately(string word1, string word2) {
        string res { "" };
        const int min_size = std::min(word1.size(), word2.size());
        for (int i=0; i<min_size; i++) {
			res += word1[i];
			res += word2[i];
        }
        res += word1.substr(min_size) + word2.substr(min_size);
        return res;
}

int main ()
{
	
	std::cout << mergeAlternately("hola", "mundo") << std::endl;

	return 0;
}

