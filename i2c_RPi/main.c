/*
 * Raspberry i2c Test
  */
  
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	const char *i2cDevice = "/dev/i2c-1";
	const int i2cAddress = 0x07;
	unsigned char buf[8];
	int fd;
	
	printf("***** RPi i2c Arduino test *****\n");

	if ((fd = open(i2cDevice, O_RDWR)) < 0) 
	{
		printf("Failed to open i2c port\n");
		exit(1);
	}
	
	 // set address
	if (ioctl(fd, I2C_SLAVE, i2cAddress) < 0) {
		printf("Unable to configure i2c address\n");
		exit(1);
	}
	
	// Read
	if (read(fd, buf, 8) != 8) 
	{
		// read back data into buf
		printf("Short read from i2c\n");
		exit(1);
	}

	// Show Values we read
	printf("%d  %d  %d  %d  %d  %d  %d  %d\n",
		(int)buf[0],
		(int)buf[1],
		(int)buf[2],
		(int)buf[3],
		(int)buf[4],
		(int)buf[5],
		(int)buf[6],
		(int)buf[7]
	);
	
	// Done
	close(fd);

	printf("***** RPi i2c Arduino end *****\n");
	
	return (0);
}
