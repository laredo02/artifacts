
#include <iostream>
#include <string>


using namespace std;

int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size())
            return -1;
        if (needle.size() == 0)
            return 0;

        int hsize = haystack.size();
        int nsize = needle.size();

        int i, j;
        bool found = true;
        for (i = 0; i<hsize; i++) {
            if (haystack[i] == needle[0] && (nsize <= hsize-i)) {
                for (j=1; j<nsize;) {
                    if (haystack[i+j] == needle[j]) {
                		if (j==nsize-1)
							return i;
                        j++;
					} else {
                        j=1;
                        break;
					}
                }
            }
        }

        return -1;

    }

int main ()
{
	std::cout << strStr("sadbudsad", "sad") << std::endl;
	std::cout << strStr("leetcode", "leeto") << std::endl;
	std::cout << strStr("hello", "ll") << std::endl;

	return 0;
}




