# Arduino projects for ESP8266 and ESP8266MOD

This is a compilation of various projects for ESP8266 and ESP8266MOD. However, the code can run on most Arduino devices with minor modification. 

There are instructions in the the readme of each folder/project, along with pictures of the setup. The code itself is commented and tried to make easy to understand.


## Projects

* [mqtt_led](https://github.com/sondrew/ESP8266/tree/master/mqtt_led)
This project is using the MQTT protocol to receive commands and execute light functions on LEDs. Good introduction to MQTT using built-in LED and 4 monochrome LEDs.
* [mqtt_potentiometer](https://github.com/sondrew/ESP8266/tree/master/mqtt_potentiometer)
First part of code for a two device project. Run this code on one ESP8266 device and run mqtt_servo on another. Publishes data using MQTT when user rotates a potentiometer and controls the servo on the other device.
* [mqtt_servo](https://github.com/sondrew/ESP8266/tree/master/mqtt_servo)
Second part of code for a two device project. Run this code on one ESP8266 device and run mqtt_potentiometer on another. Receives data using MQTT to control/rotate a servo, corresponding to a potentiometer on another device.
* [rfid_read](https://github.com/sondrew/ESP8266/tree/master/rfid_read)
Simple RFID read of a tag's ID.
* [rfid_read_store](https://github.com/sondrew/ESP8266/tree/master/rfid_read_store)
Extention of the rfid_read, including code to store and recognize specific tags, both before and in runtime.
* [rfid_mqtt](https://github.com/sondrew/ESP8266/tree/master/rfid_mqtt)
Extention of the rfid_read_store, using MQTT to publish recognized tags.
* [ultrasonic_distance](https://github.com/sondrew/ESP8266/tree/master/ultrasonic_distance)
Distance measuring using ultrasonic sensor (HC-SR04) and ESP8266MOD. Uses 5v supply and outputs distance in cm. 

## Prerequisite

Arduino IDE with [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) installed.

-   Install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the  [Arduino website](http://www.arduino.cc/en/main/software).
-   Start Arduino and open Preferences window.
-   Enter  `http://arduino.esp8266.com/stable/package_esp8266com_index.json`  into  _Additional Board Manager URLs_  field. You can add multiple URLs, separating them with commas.
-   Open Boards Manager from Tools > Board menu and install  _esp8266_  platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

## Libraries
All libraries used in these projects can be found in Library Manager in the Arduino IDE with the given name below, and Github links are included for manual download. 

* [PubSubClient](https://github.com/knolleary/pubsubclient) by Nick O'Leary (MQTT)
* [MFRC522](https://github.com/miguelbalboa/rfid) by GithubCommunity (RFID)
* [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) by Ivan Grokhotkov (included in ESP8266 Arduino Core)
* [Serial Peripheral Interface (SPI)](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/SPI) by Arduino (included in Arduino IDE)

 ## Devices used

### ESP8266
Standard LoLin ESP8266 with NodeMCU v3

Front side
![ESP8266 front](https://image.ibb.co/exRRfS/IMG_0657.jpg)

Back side
![ESP8266 back](https://image.ibb.co/g3DiS7/IMG_0662.jpg)

### ESP8266MOD
ESP8266 modification with 5v supply

Front side
![ESP8266MOD front](https://image.ibb.co/bP3iS7/IMG_0672.jpg)

Back side
![ESP8266MOD back](https://image.ibb.co/mDY6fS/IMG_0673.jpg)

### ESP32 / ESP-WROOM-32
MH-ET LIVE ESP32 (ESP-WROOM-32). Haven't used this device much in these projects.

Front side
![ESP32 front](https://image.ibb.co/dbje0S/IMG_0665.jpg)

Back side
![ESP32 back](https://image.ibb.co/hVUq77/IMG_0668.jpg)
