i2c-read: i2c-read.c
	gcc -Wall -o i2c-read i2c-read.c -lwiringPi

spi-i2c-read: spi-i2c-read.c
	gcc -Wall -o spi-i2c-read spi-i2c-read.c -lwiringPi

orient3d: orient3d.c
	gcc -Wall -o orient3d orient3d.c -lwiringPi

movearound: movearound.c
	gcc -Wall -o movearound movearound.c -lwiringPi
