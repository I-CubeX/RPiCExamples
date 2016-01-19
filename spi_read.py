import spidev
import time
import os

from turtle import *

canvas = Screen()
canvas.setup(400,200)
 
# Open SPI bus
spi = spidev.SpiDev()
spi.open(0,0)
 
# Function to read SPI data from MCP3008 chip
# Channel must be an integer 0-7
def ReadChannel(channel):
  adc = spi.xfer2([1,(8+channel)<<4,0])
  data = ((adc[1]&3) << 8) + adc[2]
  return data
 
# Define delay between readings
delay = 0.05

myTurtle = Turtle()
 

try:

  while True:

    sensor_1 = ReadChannel(0);
    sensor_2 = ReadChannel(1);
    
    # Print out results
    print "--------------------------------------------"
    print("Sensor 1 {}".format(sensor_1))
    print("Sensor 2 {}".format(sensor_2))

    # Turn the turtle with sensor 2
    if sensor_2 > 100:
       print("\nTurn!!\n")
       myTurtle.left(90)

    # Change turtle size with sensor 1
    turtleSize = 2 + sensor_1/50.0

    myTurtle.shapesize(turtleSize, turtleSize, 1)
    
    
    # Wait before repeating loop
    time.sleep(delay)
except KeyboardInterrupt:
    pass
