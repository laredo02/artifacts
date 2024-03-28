
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, const char **argv) {

	if (argc < 2) {
		fprintf(stderr, "ERROR: too few arguments\n");
		exit(1);
	} else if (argc > 2) {
		fprintf(stderr, "ERROR: too many arguments\n");
		exit(1);
	}

	int fd = open(argv[1], O_WRONLY);
	if (fd == -1) {
		perror("ERROR:");
		exit(1);
	}

	char *buf = "HOLAMUNDO";
	lseek(fd, 0, SEEK_END);
	struct stat fd_stat;
	printf("Writing %ld bytes to %s...\n", SSIZE_MAX, argv[0]);
	while (fd_stat.st_size < strlen(buf)*50 /*SSIZE_MAX-strlen(buf)*/) {
		printf("Size written: %ld\n", fd_stat.st_size);
		ssize_t wlen = write(fd, buf, strlen(buf));
		if (wlen == -1) {
			perror("ERROR:");
			exit(1);
		}
		fstat(fd, &fd_stat);
	}
	close(fd);

	return 0;
}

