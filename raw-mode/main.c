
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

struct termios orig_term;
char key;
int terminate_flag = 0;

void disableRawMode () {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_term);
}

void enableRawMode () {
	tcgetattr(STDIN_FILENO, &orig_term);
	atexit(disableRawMode);
	struct termios raw_term = orig_term;
	raw_term.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	raw_term.c_oflag &= ~OPOST;
	raw_term.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	raw_term.c_cflag &= ~(CSIZE | PARENB);
	raw_term.c_cflag |= CS8;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_term);
}

void terminate () {
	write(STDOUT_FILENO, "\x1b[0m", 4);
	write(STDOUT_FILENO, "\x1b[J", 4);
	exit(0);
}

void clearScreen () {
	write(STDOUT_FILENO, "\x1b[48;2;0;0;0m", 13);
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	write(STDOUT_FILENO, "\x1b[48;2;255;255;255m", 19);
}

int pollEvents () {
	while (!terminate_flag) {
		read(STDIN_FILENO, &key, 1);
		if (key == 'q') {
			terminate_flag = 1;
			exit(0);
		}
	}
	return 0;
}

int createThread (int (*fn)(void *), void *buffer) {
	char *stackhead = buffer + strlen(buffer)-1;
	int tid = clone(fn, stackhead, CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, 0);
	if (tid == -1) {
		perror("ERROR");
		exit(1);
	}
	else return tid;
}

int main ()
{
	enableRawMode();
	
	struct timespec time, _time;
	time.tv_sec = 0;
	time.tv_nsec = (long) 1000000000/60;

	char *stack = (char *) malloc(1024);
	pid_t tid = createThread(pollEvents, stack);
	if (tid == -1) {
		free(stack);
		exit(0);
	}

	while (!terminate_flag) {
		clearScreen();

		nanosleep(&time, NULL);
	}

	int wstatus;
	waitpid(tid, &wstatus, 0);

	terminate();
	return 0;
}




