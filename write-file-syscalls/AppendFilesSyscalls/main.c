
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, const char **argv) {
	int fd = open("file.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1) {
		exit(1);
	}
	char *buf = "Lorem Ipsum\n";
	for (int i=0; i<; i++) {
		ssize_t wle = write(fd, buf, strlen(buf));
		lseek(fd, 0, SEEK_END);
	}
	return 0;
}

