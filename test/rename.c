#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>  /* Many POSIX functions (but not all, by a large margin) */
#include <sys/stat.h>
#include <fcntl.h>   /* open(), creat() - and fcntl() */



int main(int argc, char **argv)
{
	int i;
	const char *name = "tmp", *alter = "alter";

	rename(name, alter);

	return 0;
}

