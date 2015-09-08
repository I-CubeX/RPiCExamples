
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
   if ( (dev = wiringPiI2CSetup(0x17)) == -1) {
      printf("error init i2c at 0x17\n");
      return -1;
   }
   else
      printf("i2c init at 0x17 OK, dev = %i\n",dev);
   while (1)
   {
      int val = wiringPiI2CRead(dev);
      printf("val = %i\n", val);
   }
   return 0;
}
