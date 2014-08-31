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

int ee24c02_write_page(int file, unsigned char address, unsigned char *data, unsigned int len)
{
	unsigned char buffer[9];
	if(len > 8)
		return -1;

	buffer[0] = address;
	memcpy(buffer+1, data,len);

	return write(file, buffer, len+1) - 1;
}

int ee24c02_write(int file, unsigned char address, unsigned char *data, int len)
{
	int ret=0, nbytes;
	if(len + address > 256)
		len = 256-address;		// prevent roll over
	while(len > 0)
	{
		nbytes = 8 - (address % 8);	// max bytes you can read without roll over
		nbytes = (len < nbytes ? len : nbytes);		// choose min
		if (ee24c02_write_page(file, address, data, nbytes) != nbytes)
			return -1;

	usleep(10000);		// twice the max stated in the doc
		len -= nbytes;
		address += nbytes;
		data += nbytes;
	}
	return len;
}


int main(int argc, char const *argv[])
{
	int file, i, len;
	unsigned char *ptr;

	if (argc != 3)
	{
		printf("Usage:\nee24c02w.bin /dev/i2c string");
		fflush(stdout);
		exit(1);
	}
	if ((file = open(argv[1],O_RDWR)) < 0) {
		printf("Failed to open the bus %s\n", argv[1]);
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, 0x50) < 0)
	{
		printf("Cannot init chip address\n");
		exit(1);
	}

	ee24c02_write(file, 100, (unsigned char*) argv[2], strlen(argv[2]));
	
	close(file);
	exit(0);
}