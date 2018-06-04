#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

/**
 * Checking argument is number or not
 * on success, it returns true
 * on failure, it returns false
 */

bool check_for_number(char number[])
{
	int i = 0;

	if (number[0] == '-')
		i = 1;								//checking for negative numbers

	for (; number[i] != 0; i++) {
		if (!isdigit(number[i]))
			return false;
	}

	return true;
}

/**
 * Command line argument should be digit
 * Checking for string, no of arguments
 * on success, it returns 0
 * on failure, it returns -1
 */

int validate_cmd_args(int argc, char *argv[])
{
	int seconds = 0;

	switch (argc){

		case 1: 
			printf ("usage: <%s> <number of seconds to capture>\n", argv[0]);
			return -1;

		case 2:
			if (false == check_for_number(argv[1])) {
				printf ("number is not valid Please Check number once agian\n");
				return -1;
			}

			seconds = atoi (argv[1]);
			return seconds;

		default:
			printf ("Exceed number of arguments\nFor ex ./app 120\n");
			return -1;
	}
}

int main (int argc, char *argv[])
{
	int fd;
	int seconds;

	if ((seconds = validate_cmd_args(argc, argv)) == -1) 
		return 1;

	fd = open ("/dev/vedio0", O_RDWR);

	if(fd < 0) {
		perror("unable to open the device");
	} else {
		printf("file opened successfully %d \n", fd);
	}

	printf ("pid is : %d \n", getpid());	

	ioctl (fd, getpid(), 1);	// for stream on, sending value 1

	sleep (seconds);			// Module will capture for no of seconds

	ioctl (fd, getpid(), 0);	// for stream off, sending value 0

	close (fd);

	return 0;
}
