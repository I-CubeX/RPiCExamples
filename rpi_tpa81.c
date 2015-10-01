// TPA81 example c code for the Raspberry pi.
//
// Reads the software revision of the TPA81 and all temperature data
// and then prints to the screen.
//
// By James Henderson 2012.

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("**** TPA81 test program ****,\n");
	int fd;														// File descrition
	char *fileName = "/dev/i2c-1";								// Name of the port we will be using
	int  address = 0x68;										// Address of TPA81 shifted right 1 bit
	unsigned char buf[10];										// Buffer for data being read/ written on the i2c bus
	
	if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	
	if (ioctl(fd, I2C_SLAVE, address) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}
	
	
	buf[0] = 0;													// This is the register we wish to read from
	
	if ((write(fd, buf, 1)) != 1) {								// Send register to read from
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	if (read(fd, buf, 10) != 10) {								// Read back data into buf[]
		printf("Unable to read from slave\n");
		exit(1);
	}
	else {
		printf("Software v: %u \n",buf[0]);
		printf("Ambient temperature: %u \n",buf[1]);
		printf("Temperature readings:\n");
		printf("%2u, %2u, %2u, %2u \n", buf[2], buf[3], buf[4], buf[5]);
		printf("%2u, %2u, %2u, %2u\n", buf[6], buf[7], buf[8], buf[9]);	
	}
	
	return 0;
}


