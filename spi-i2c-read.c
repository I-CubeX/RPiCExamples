
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp3004.h>

#define BASE 100 //mcp3004/8
#define SPI_CH 0
#define I2C_ADDR 0x60

int main(int argc, char *argv[])
{
   int dev;
   if (wiringPiSetup() == -1) {
      printf("wiringPi init failed\n");
      return -1;
   }

   pullUpDnControl(8, PUD_UP);
   pullUpDnControl(9, PUD_UP);
   if ( (dev = wiringPiI2CSetup(I2C_ADDR)) == -1) {
      printf("error init i2c at %#04x\n",I2C_ADDR);
      return -1;
   }
   else
      printf("i2c init at %#04x OK, dev = %i\n",I2C_ADDR, dev);

   mcp3004Setup(BASE,SPI_CH);

   while (1)
   {
      //int val = wiringPiI2CRead(dev);
      int val = wiringPiI2CReadReg8(dev, 0x01);
      int pitch = wiringPiI2CReadReg8(dev, 0x04);
      int roll = wiringPiI2CReadReg8(dev, 0x05);
      int sval = analogRead(BASE + 0);
      printf("i2c bearing = %3i   i2c pitch = %3i  i2c roll = %3i   spi0 val = %3i \n", val, pitch, roll, sval);
   }
   return 0;
}
