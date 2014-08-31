/*
 * Copyright (c) 2014 Charles-Henri Mousset
 * Distributed under the GNU GPL v2. For full terms see the file LICENSE
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>


int main(int argc, char const *argv[])
{
	int file;
	int len = 256;
	unsigned char buffer[len];

	if (argc != 2)
	{
		printf("Usage:\nedid.bin /dev/i2c");
		exit(1);
	}
	if ((file = open(argv[1],O_RDWR)) < 0) {
		printf("Failed to open the bus %s\n", argv[1]);
		exit(1);
	}

	// connect to EID chip
	if (ioctl(file, I2C_SLAVE, 0x50) < 0)
	{
		printf("Cannot init chip address\n");
		exit(1);
	}

	buffer[0] = 0;
	if(write(file, buffer, 1) != 1)
	{
		printf("error: %s\n", strerror(errno));
		exit(1);
	}

	if (read(file, buffer, len) != len)
	{
		printf("error : %s\n", strerror(errno));
		exit(1)	;
	}
	close(file);

	int i, j;
	printf("DATA :");
	for (i=0; i<len; i++)
	{
		if((i%16) == 0)
			printf("\n");
		printf("%02X ", buffer[i]);
	}
	printf("\n");
	return 0;
}