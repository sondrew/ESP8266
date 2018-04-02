/*
* Ultrasonic sensor distance measuring with ESP8266MOD (with 5v)
*
* This code is for using an ultrasonic sensor (HC-SR04) to measure distance. 
* In this example I've used the ESP8266MOD, because my mod version of the ESP8266 has 5v. 
* The ultrasonic sensor HC-SR04 supposedly has a wide range of operating voltage, 
* but most seem to have difficulty getting it to work with 3.3v. If you want to use 
* an ultrasonic sensor with the standard ESP8266 (3.3v), you can use a logic level 
* converter to do the same thing. I haven't tried this specifically, but there are 
* many tutorials online (two examples linked in README.md)
* 
*/

// Define pin connections
#define TRIGGER D1
#define ECHO    D2

// Define variables
long duration, distance;            // Variables for calculating distance
const int MEASURE_INTERVAL = 1000;  // Interval between each distance measurement

void setup() {
  Serial.begin (115200);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 

  // Set the trigger pin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW);

  // Read the echo pin, return the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH);
  // Calculate the distance
  distance = (duration/2) / 29.1;

  // Output the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Delay loop for given interval
  delay(MEASURE_INTERVAL);
}
