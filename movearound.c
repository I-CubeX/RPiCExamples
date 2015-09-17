
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define I2C_ADDR 0x68
#define REG_START 0x01

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
      int i;
      for (i=0; i<9; i++) {
         wiringPiI2CWrite(dev,REG_START+i);
         int val = wiringPiI2CReadReg8(dev,REG_START+i);
         printf("v%i = %03i ",i, val);
      }
      printf("\n"); 
   }
   return 0;
}
