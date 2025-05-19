#Overview
mst_iot_temperature uses an (https://www.adafruit.com/product/2821 microcontroller and a [DFrobot Fermion SHT41 breakout 
board](https://www.dfrobot.com/product-2437.html) to upload temperature and humidity data to the Adafruit IO cloud. You need to get these two components, plus a battery with JST connector if you want to operate the system without USB power. Multiple [such batteries in different sizes](https://www.adafruit.com/product/2011) can be purchased e.g. from Adafruit. 
#Connections
For this project to work, you need to physically connect the SHT41 breakout board to the Feather microcontroller. Depending on your exact configuration (male/female headers), 
you might need different types of cables. The 4 lines of the SHT41 breakout board for the I2C communication (VCC and GND for power supply, SCL and SDA for clock and data) are connected to corresponding pins on the Feather Huzzah as shown in the image below: 
![zoomed](https://github.com/user-attachments/assets/47d9a9d1-d44b-4868-b142-c64e246a3625)
