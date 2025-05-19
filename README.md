# Overview
mst_iot_temperature uses a [Feather Huzzah microcontroller](https://www.adafruit.com/product/2821) and a [DFrobot Fermion SHT41 breakout 
board](https://www.dfrobot.com/product-2437.html) to upload temperature and humidity data via WLAN to the Adafruit IO cloud. You can run the system either on USB power, or you can buy a battery with JST connector if you want a few days of temperature logging without external power. Multiple [such batteries in different sizes](https://www.adafruit.com/product/2011) can be purchased e.g. from Adafruit. 
# Physical connections
## Connection of the breakout board
For this project to work, you need to physically connect the SHT41 breakout board to the Feather microcontroller. Depending on your exact configuration (male/female headers), you might need different types of cables. The SHT41 breakout board has 4 connections, labelled VCC, GND, SCL and SDA. These are supply power (VCC), ground (GND), serial clock (SCL) and serial data (SDA). First, we need to power it by connecting VCC and GND to the pins of the Feather PCB shown below. 

![I2CPower](https://github.com/user-attachments/assets/8dbe8aa7-1b3e-43a2-95c2-d43b5c664d08)

Next, we have to connect SCL and SDA to the corresponding pins on the Feather PCB, shown in the next image.

![I2C](https://github.com/user-attachments/assets/32114353-9b83-40c1-9842-c613962e0f6c)

With this, the SHT41 breakout board is connected, and we don't need to set up anything further about the pins used, since they are all already doing the right thing by default. 
## Connection for deep sleep
The microcontroller will go into deep sleep mode most of the time, and wake itself up. This needs an external connection of pin 16 to the reset pin, shown in the picture below.

![Reset](https://github.com/user-attachments/assets/277907f8-d2f5-4613-80e5-d13fb08def17)

The final setup should look something like this: 

![zoomed](https://github.com/user-attachments/assets/47d9a9d1-d44b-4868-b142-c64e246a3625)

# Prerequisites
## Driver for the Feather Huzzah
First, you have to install the driver for the [Feather Huzzah board](http://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers). Download the zip-file "CP210X universal windows driver", extract it, right-click on the .inf file and choose "install". 

## Arduino IDE
Next, if you do not already have it installed, you need to install the [Arduino IDE](http://www.arduino.cc/en/Main/Software). Start it after installation, it might install some additional updates. 

## Feather board package
In the Arduino IDE, you have to install the "Board package" for the Feather Huzzah. In the menu, select file->preferences... and fill the dialog as follows:

![boardpackage](https://github.com/user-attachments/assets/0078a219-0d18-46d0-9e08-942504813f2f)

Now connect the Feather Huzzah to your PC, and choose the Feather Huzzah ESP8266 in the white "select board" field in the the title bar of the Arduino IDE.

![selectboard](https://github.com/user-attachments/assets/a6e242d7-a16e-412f-998f-6b879e6cec3e)

![selectboard](https://github.com/user-attachments/assets/977a9a13-5195-4140-a191-4fc3005e734f)

A message will appear telling you to install "esp8266 core", so do that. When these steps are done, you should have an empty Arduino sketch (program) in your Arduino IDE consisting of a setup() and loop() function.

## Libraries
Finally, you need to install libraries for both the SHT41 breakout board and for the Adafruit IO cloud. For the SHT41, follow the steps in the image below. If you chosse "install all" in the first dialog, it will install the BusIO library automatically, otherwise you need to add it manually like at the end of the instructions in the image below. 

![sht4xlibrary](https://github.com/user-attachments/assets/e0cf72af-e66a-4989-a128-83bb75c9d8f6)

The second necessary library is for the Adafruit IO cloud. Install it via the library manager like before

![adafruitIO](https://github.com/user-attachments/assets/0168af89-52e6-4bd3-b0b6-d16cc08ec859)

# Adafruit IO, part I
## Create account
We will be uploading data to an IoT cloud service. There are lots of them out there, and I chose that of Adafruit because it is free for "low" usage. Go to the [Adafruit IO homepage](https://accounts.adafruit.com/ ) and create a new account. You will need to verify your account after creating it by an email link. Once this is done, you can login to your Adafruit IO account by clicking IO in the menu on the top right of the website. 

![iologin](https://github.com/user-attachments/assets/6f278908-4ce0-4af6-9bcd-a29499998e0b)
## Get your login credentials
Once you are logged in to Adafruit IO, click the key symbol in the top right to get your login credentials. 

![key](https://github.com/user-attachments/assets/e1732dfa-f306-4ef7-a34f-98f5f9bcaf8d)

You will see code for Arduino, copy it:

![credentials](https://github.com/user-attachments/assets/f9dee591-9bee-4846-b236-37812d9741b1)

Now we are finally ready to code something!

# Code

## Overview
Standard Arduino code consists of two main functions called setup() and loop(); setup() is executed at startup once, and then loop() is executed repetitively. 
The Arduino code for this program is slightly unusual because the loop() function is empty. The reason is that the whole program only runs in the setup() function, and at the end of that function, the microcontroller is put into deep sleep mode, from which it is woken by a signal on the reset pin - so after waking up, it starts over again in the setup() function,  never actually getting to the loop().
Apart from getting a temperature and humidity reading from the sensor, and uploading that data to the Adafruit IO cloud, the code also prints the values read so you can view what is going on with the serial monitor, it turns on the red LED on the Feather PCB while it is measuring so you know when it is active (and that it is active, when it is running standalone). That's all the code does, the program is very basic. 

## Running the program
Copy the code (single .ino file in this repository), delete the code in the open empty sketch, and replace it with the copied code. At the top of the file, you will find 4 defines, which you need to change:

![defines](https://github.com/user-attachments/assets/72189822-cd50-4a87-86d3-47108375740b)

Make sure to keep the quotation marks, but replace the Adafruit IO and WLAN names and passwords with your login credentials. Once you have done this, you should be able to run the program by clicking the run button in the title bar of the Arduino IDE.

![run](https://github.com/user-attachments/assets/0b25dafc-98d2-43f9-b330-3491471aa57b)

Open the serial monitor to see the output of the program by clicking on the serial monitor button on the top right of the Arduino IDE window/toolbar. 

![serialmonitor](https://github.com/user-attachments/assets/24185213-608f-4cef-9892-0a2aec44789f)

Your output should look a bit like this:

![serialout](https://github.com/user-attachments/assets/5cb917ad-8e67-4f1d-a990-0f3e20f868c1)

# Adafruit.IO, Part II

Once you see that your program is running, you can view your data directly by looking at the Feeds tab in Adafruit.io, or you can create a dashboard which shows a graph of the data easily. 

![dashboard](https://github.com/user-attachments/assets/4bc5d776-0801-417a-87b2-5cc618a03ab9)

If you have any suggestions for improvements or extensions, let me know!

