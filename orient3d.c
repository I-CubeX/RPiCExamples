
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define I2C_ADDR 0x60
#define REG_BEAR 0x01
#define REG_PITCH 0x04
#define REG_ROLL 0x05

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
      printf("error init i2c at 0x%04x\n",I2C_ADDR);
      return -1;
   }
   else
      printf("i2c init at 0x%04x OK, dev = %i\n", I2C_ADDR, dev);
   while (1)
   {
      int bearing = (int)wiringPiI2CReadReg8(dev,REG_BEAR);
      int pitch = (int) wiringPiI2CReadReg8(dev, REG_PITCH);
      int roll = (int) wiringPiI2CReadReg8(dev, REG_ROLL);
      printf("bearing = %03i pitch = %03i roll = %03i\n",bearing, pitch, roll);
   }
   return 0;
}
