i2c-read: i2c-read.c
	gcc -Wall -o i2c-read i2c-read.c -lwiringPi

spi-i2c-read: spi-i2c-read.c
	gcc -Wall -o spi-i2c-read spi-i2c-read.c -lwiringPi

spi-read8: spi-read8.c
	gcc -Wall -o spi-read8 spi-read8.c -lwiringPi

orient3d: orient3d.c
	gcc -Wall -o orient3d orient3d.c -lwiringPi

movearound: movearound.c
	gcc -Wall -o movearound movearound.c -lwiringPi


magnetic3d: magnetic3d.c
	gcc -Wall -o magnetic3d magnetic3d.c -lwiringPi


moist: moist.c
	gcc -Wall -o moist moist.c -lwiringPi

mag_ori3d : mag_ori3d.c
	gcc -Wall -o mag_ori3d mag_ori3d.c -lwiringPi
