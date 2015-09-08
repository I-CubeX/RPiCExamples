i2c-read: i2c-read.c
	gcc -Wall -o i2c-read i2c-read.c -lwiringPi

spi-i2c-read: spi-i2c-read.c
	gcc -Wall -o spi-i2c-read spi-i2c-read.c -lwiringPi
