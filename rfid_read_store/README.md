# RFID read and store using ESP8266

Code example for reading and storing the ID of a RFID/NFC tag with ESP8266.
Reads a RFID tag and output its UID values in hex and decimal.
Doesn't output UID of tag if it's the same tag as the last one read.
UID of tags are usually output in hex, but I've included output in dec, 
as is much simpler to store and compare.

User can store tags in runtime by giving the last read tag a name and 
sending it in Serial monitor. Every subsequent read of that tag will now 
display its name. You can fill in your own code do perform specific actions, 
depending on specific cards. If you want to have tags pre-stored at runtime, 
just hardcode the decimal UID of the tag in 'idStoredTags' and the String 
name in 'nameStoredTags'. For example:

```
// Replace these lines
unsigned long idStoredTags[MAX_STORED_TAGS];  // Array containing decimal value UID of tags
String nameStoredTags[MAX_STORED_TAGS];       // Array containing user-defined names of tags

// With your own tags
unsigned long idStoredTags[] = {0123456789, 1234567890, 2345678910};
String  nameStoredTags[] = {"Omar", "McNulty", "Bubbles"};
```

Code example for simple reading the ID of a RFID/NFC tag using  ESP8266. 
Reads a RFID tag and output its UID values in hex and decimal. 
Doesn't output UID of tag if it's the same tag as the last one read. 
UID of tags are usually output in hex, but I've included output in decimal, 
as it is much simpler to store and compare.

I've tested this example and got it working well on both ESP8266 and ESP8266MOD, 
but it should work fine on any Arduino unit. 

This example is for RFID UID read and store, check out my other RFID examples as well:  
* [rfid_read](https://github.com/sondrew/ESP8266/tree/master/rfid_read) - simple read of RFID tags
* [rfid_mqtt](https://github.com/sondrew/ESP8266/tree/master/rfid_mqtt) -  read and store tags, publish tags with MQTT  

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


## Images ESP8266

![ESP8266](https://image.ibb.co/fsGsKn/IMG_0617.jpg)

![ESP8266](https://preview.ibb.co/bFSckS/IMG_0612.jpg)

![ESP8266](https://image.ibb.co/jp4CKn/IMG_0631.jpg)


## Images ESP8266MOD

![ESP8266MOD](https://image.ibb.co/kCbdQS/IMG_0598.jpg)

![ESP8266MOD](https://image.ibb.co/nawdQS/IMG_0605.jpg)

![ESP8266](https://image.ibb.co/krXwC7/IMG_0606.jpg)

![ESP8266MOD](https://image.ibb.co/iqhk5S/IMG_0610.jpg)
