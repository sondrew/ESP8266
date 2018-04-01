# RFID read using ESP8266

Code example for simple reading the ID of a RFID/NFC tag using  ESP8266. 
Reads a RFID tag and output its UID values in hex and decimal. 
Doesn't output UID of tag if it's the same tag as the last one read. 
UID of tags are usually output in hex, but I've included output in decimal, 
as it is much simpler to store and compare.

I've tested this example and got it working well on both ESP8266 and ESP8266MOD. 

This example is an simple RFID UID read, if you want to do more, check out my other RFID examples:  
* [rfid_read_store](/tree/master/rfid_simple_read) - read, store and recognize stored tags  
* [rfid_mqtt](/tree/master/rfid_mqtt) -  read and store tags, publish read tags with MQTT  

## Prerequisite
Install the library 'MFRC522' by 'GithubCommunity' in the Arduino IDE, 
or download here: https://github.com/miguelbalboa/rfid

## Pin connections

| Signal        | RFID reader<br>(MFRC522) | NodeMCU<br>(ESP8266) | Arduino UNO/101 | Generic |
|---------------|:-------------:|:--------------:| :------:|:------------:|
| RST/Reset     | RST           | D3             | 9       | GPIO-0       |
| SPI SS        | SDA           | D8             | 10      | GPIO-15      |
| SPI MOSI      | MOSI          | D7             | 11      | GPIO-13      |
| SPI MISO      | MISO          | D6             | 12      | GPIO-12      |
| SPI SCK       | SCK           | D5             | 13      | GPIO-14      |


Pin connections for all Arduino boards: https://www.arduino.cc/en/Reference/SPI  

## Images

### ESP8266

![ESP8266](https://image.ibb.co/fsGsKn/IMG_0617.jpg)

![ESP8266](https://preview.ibb.co/bFSckS/IMG_0612.jpg)

![ESP8266](https://image.ibb.co/jp4CKn/IMG_0631.jpg)


### ESP8266MOD

![ESP8266MOD](https://image.ibb.co/kCbdQS/IMG_0598.jpg)

![ESP8266MOD](https://image.ibb.co/nawdQS/IMG_0605.jpg)

![ESP8266](https://image.ibb.co/krXwC7/IMG_0606.jpg)

![ESP8266MOD](https://image.ibb.co/iqhk5S/IMG_0610.jpg)
