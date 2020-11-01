#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>  /* Many POSIX functions (but not all, by a large margin) */
#include <sys/stat.h>
#include <fcntl.h>   /* open(), creat() - and fcntl() */



int main(int argc, char **argv)
{
	int i;
	if (argc != 2) {
		return -1;
	}

	const char *name = argv[1];

	creat(name, 0777);

	return 0;
}

