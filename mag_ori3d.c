
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>
#include <stdint.h>

#define I2C_ADDR 0x1e
#define REG_START 0x03
uint8_t values[6];

#define I2C_ADDR_O3D	0x60
#define REG_BEAR	0x01
#define REG_PITCH	0x05
#define REG_ROLL	0x05

int main(int argc, char *argv[])
{
   int dev;

   int dev_o3d;

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


   if ( (dev_o3d = wiringPiI2CSetup(I2C_ADDR_O3D)) == -1) {
      printf("error init i2c at 0x%04x\n",I2C_ADDR_O3D);
   }

   while (1)
   {
      int i; //NOTE: for some reason, consecutive writes don't work
             //so we must use WriteReg8
      wiringPiI2CWriteReg8(dev,0x2, 0x01);
      //wiringPiI2CWrite(dev,0x1);
      delayMicroseconds(6000); //takes 6ms between each read
      for (i=0; i<6; i++) {
         wiringPiI2CWrite(dev,REG_START+i);
         uint8_t val = wiringPiI2CRead(dev);
         //printf("%03i  ", val);
         values[i] = val;
      }

      //scaling into uTeslas:
      //assuming default gain of 1.3 (see adafruit HMC5883 library for details)
      int x = (int16_t) (values[1] + (int16_t) (values[0] << 8));
      int z = (int16_t) (values[3] + (int16_t) (values[2] << 8));
      int y = (int16_t) (values[5] + (int16_t) (values[4] << 8));

      float X = x/1100.0 * 100.0;
      float Y = y/1100.0 * 100.0;
      float Z = z/980.0 * 100.0;

      int bearing = (int)wiringPiI2CReadReg8(dev_o3d,REG_BEAR);
      int pitch = (int) wiringPiI2CReadReg8(dev_o3d, REG_PITCH);
      int roll = (int) wiringPiI2CReadReg8(dev_o3d, REG_ROLL);

      printf("X = %3.2f Y = %3.2f Z = %3.2f BEAR = %03i P = %03i R = %03i\n",X,Y,Z, bearing, pitch, roll); 

   }
   return 0;
}
