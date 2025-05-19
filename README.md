# Overview
mst_iot_temperature uses an (https://www.adafruit.com/product/2821 microcontroller and a [DFrobot Fermion SHT41 breakout 
board](https://www.dfrobot.com/product-2437.html) to upload temperature and humidity data to the Adafruit IO cloud. You need to get these two components, plus a battery with JST connector if you want to operate the system without USB power. Multiple [such batteries in different sizes](https://www.adafruit.com/product/2011) can be purchased e.g. from Adafruit. 
# Physical connections
## Connection of the breakout board
For this project to work, you need to physically connect the SHT41 breakout board to the Feather microcontroller. Depending on your exact configuration (male/female headers), 
you might need different types of cables. The 4 lines of the SHT41 breakout board for the I2C communication (VCC and GND for power supply, SCL and SDA for clock and data) are connected to corresponding pins on the Feather Huzzah as shown in the image below. No further setup in the code is required, since these pins of the microcontroller already are doing what we need. 
![zoomed](https://github.com/user-attachments/assets/47d9a9d1-d44b-4868-b142-c64e246a3625)
## Connection for deep sleep
The microcontroller will go into deep sleep mode most of the time, and wake itself up. This needs an external connection of pin 16 to the reset pin, also shown in the picture above. 
# Code
## What this program does
The Arduino code is slightly unusual because the loop() function is empty. The reason is that the whole program only runs in the setup() function, and at the end of that function, the microcontroller goes into deep sleep mode, from which it is woken by a signal on the reset pin - so after waking up, it starts over again in the setup() function, thus never actually getting to the loop().
Apart from getting a temperature and humidity reading from the sensor, and uploading that data to the Adafruit IO cloud, the code also prints the values read so you can view what is going on with the serial monitor, it turns on the red LED on the Feather PCB while it is measuring so you know when it is active (and that it is active, when it is running standalone). That's all the code does, the program is very basic. 
## Libraries
For this program to work, you will need to install libraries: 
