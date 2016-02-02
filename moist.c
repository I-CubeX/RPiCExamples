
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdint.h>

#define I2C_ADDR 0x20
#define REG_RESET 0x06
#define REG_VERS 0x07
#define REG_TEMP 0x05
#define REG_MOIST 0x00

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
   else {
      printf("i2c init at 0x%04x OK, dev = %i\n", I2C_ADDR, dev);
      int version = (uint8_t) wiringPiI2CReadReg8(dev, REG_VERS);
     // wiringPiI2CWriteReg8(dev, 0x01, 0x20); //change device addr
      printf("Moist version %i\n", version);
      delay(1000);
      wiringPiI2CWrite(dev, REG_RESET); //just write the "reset" addr to device 
      printf("Sending reset...\n");
      delay(1000);
   }
   while (1)
   {  
      delayMicroseconds(1000*200);
      int val0 = (uint16_t)wiringPiI2CReadReg16(dev,REG_TEMP);
      printf("val = %03i\n", val0);
   }
   return 0;
}
