
#include <stdio.h>

// only working with the least significant nibble of the byte

void foo (unsigned char bits) {
	if ((bits & 0x00) != 0) printf("RED\n");
	if ((bits & 0x01) != 0) printf("BLUE\n");
	if ((bits & 0x02) != 0) printf("YELLOW\n");
	if ((bits & 0x04) != 0) printf("MAGENTA\n");
	if ((bits & 0x08) != 0) printf("CYAN\n");
}

int main () {
	unsigned char bits = 0x01 | 0x02; // 0001 | 0010 = 0011
	foo(bits);
	return 0;
}


