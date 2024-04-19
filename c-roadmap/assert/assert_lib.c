#include <stdio.h>
#include <assert.h>

int main ()
{
	int x, y;
	x = 100;
	y = 200;
	int z = x+y;
	assert(z == 400);
	printf("%d\n", z);
	return 0;
}

