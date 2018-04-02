# Ultrasonic distance measuring using ESP8266MOD

This is an example code fore using an ultrasonic sensor (HC-SR04) for distance measuring. In this example I've used the ESP8266MOD, because my mod version of the ESP8266 has 5v. The ultrasonic sensor supposedly has a wide range of operating voltage, but most seem to have difficulty getting it to work with 3.3v. If you want to use an ultrasonic sensor with the standard ESP8266 (3.3v), you can use a logic level converter to do the same thing. I haven't tried this specifically, but there are many tutorials online (check out examples by [instructables](http://www.instructables.com/id/A-Quick-Guide-on-Logic-Level-Shifting/) and [14core](http://www.14core.com/wiring-esp8266-with-bi-directional-logic-converter/)).

The example code is uncomplicated and commented to be easily understood.

## Pin connections

Pretty straight forward. Trigger and echo can be connected to any digital pin, presuming their pinMode is declared as output and input respectively.

| Ultrasonic sensor<br>(HC-SR04) | ESP8266MOD<br>(5v version) |
|--|--|
| Vcc | 5v |
| Ground (Gnd) | G (Gnd) |
| Trigger (Trig) | D1 [*] |
| Echo | D2 [*] |

[*] Configurable


## Images

![ESP8266MOD](https://image.ibb.co/iWnFqS/IMG_0645.jpg)

![ESP8266MOD](https://image.ibb.co/dU5Pjn/IMG_0647.jpg)

![ESP8266MOD](https://image.ibb.co/nckeH7/IMG_0649.jpg)

![ESP8266MOD](https://image.ibb.co/eY8zH7/IMG_0652.jpg)
