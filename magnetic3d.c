
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_ADDR 0x1e
#define REG_START 0x03

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
      int i; //NOTE: for some reason, consecutive writes don't work
             //so we must use WriteReg8
      wiringPiI2CWriteReg8(dev,0x2, 0x01);
      //wiringPiI2CWrite(dev,0x1);
      delayMicroseconds(7000);
      __u8 vals[6];
//      i2c_smbus_read_block_data(dev, REG_START, vals);
//      for (i=0; i<6; i++) {
//         printf("%03i  ",vals[i]);
//      }
      for (i=0; i<6; i++) {
         wiringPiI2CWrite(dev,REG_START+i);
         int val = wiringPiI2CRead(dev);
         printf("%03i  ", val);
      }

      printf("\n"); 

   }
   return 0;
}
