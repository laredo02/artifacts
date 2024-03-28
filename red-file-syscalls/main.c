
// stdlib #include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// glibc
#include <fcntl.h> 	// manipulate file descriptors
#include <unistd.h> 	// POSIX API
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, const char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Too few arguments\n");
		exit(1);
	} else if (argc > 2) {
		fprintf(stderr, "Too many arguments\n");
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("ERROR");
		exit(1);
	} else {
		lseek(fd, 0, SEEK_SET);
		long n = lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);
		long int len = 1;
		ssize_t ret;
		char *buf;
		while (len != 0 && (ret = read(fd, buf, len)) != 0) {
			if (ret == -1) {
				if (errno == EINTR) continue;
				perror("READ:");
				break;
			}
			printf("%s", buf);
			len = (ret < len) ? len-ret : len;
		}
	}
	close(fd);
	return 0;
}

