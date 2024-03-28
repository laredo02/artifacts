
#include <stdio.h>

int main ()
{
	// open file
	FILE *file = fopen("file.txt", "r");

	// get file size
	fseek(file, 0, SEEK_END);
	long size = ftell(file);	
	fseek(file, 0, SEEK_SET);

	// read file and print output
	int c;
	char string[size];
	for (int i=0; (c = getc(file)) != EOF; i++) {
		string[i] = c;
	}
	printf("%s", string);

	return 0;
}

