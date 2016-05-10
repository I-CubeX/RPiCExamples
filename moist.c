
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>

#define I2C_ADDR 0x20

int ReadReg16Swap(int dev, int addr)
{
   int val = (int)wiringPiI2CReadReg16(dev,addr); //moist read
   val = (val >> 8) + ( (val & 0xFF) << 8);
   return val;
} 

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
      printf("error init i2c at 0x%04x\n", I2C_ADDR);
      return -1;
   }
   else
      printf("moist i2c init at 0x%04x OK, dev = %i\n",I2C_ADDR, dev);
   while (1)
   {  // moisture = 2 bytes read @ reg 0x00
      // temp = 2 bytes read @ reg 0x05
      // meas light = write @ 0x03
      // read light = 2 bytes read @ 0x04

      // get_busy = 2 bytes read @ 0x09
      int val;
      val = ReadReg16Swap(dev, 0x00);
      printf("moisture val = %i	 ", val);

      val = ReadReg16Swap(dev, 0x05);
      printf("temp val = %i   ", val);

      wiringPiI2CWrite(dev, 0x03); // trigger light meas
      delayMicroseconds(1500*1000); //wait one second, as this sensor is slowwww
      val = ReadReg16Swap(dev, 0x04);
      printf("light val = %i\n",val);   
   }
   return 0;
}
