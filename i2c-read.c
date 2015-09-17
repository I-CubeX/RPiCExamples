
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main(int argc, char *argv[])
{
   int dev;
   if (wiringPiSetup() == -1) {
      printf("wiringPi init failed\n");
      return -1;
   }

   pullUpDnControl(8, PUD_UP);
   pullUpDnControl(9, PUD_UP);
   if ( (dev = wiringPiI2CSetup(0x1e)) == -1) {
      printf("error init i2c at 0x1e\n");
      return -1;
   }
   else
      printf("i2c init at 0x1e OK, dev = %i\n",dev);
   while (1)
   {
      int val = (int)wiringPiI2CReadReg16(dev,0);
      printf("val = %i\n", val);
   }
   return 0;
}
