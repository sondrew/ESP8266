/**
 * Based on "Basic ESP8266 MQTT example" by the PubSubClient library
 * 
 * The intention is to run this code on an ESP8266 with a potentiometer connected,
 * and use this to control a servo on another ESP8266 using MQTT transmitting in 
 * intervals (alternatively on change). Use the 'mqtt_servo' code for the other device.
 * 
 * It listens to the potentiometer and publishes to the topic 'servo'
 */


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Change these to values suitable for your network
const char* ssid = "LAN Solo";                   // Wi-Fi name
const char* password = "EmpireDidNothingWrong";  // Wi-Fi password
const char* mqtt_server = "127.0.0.1";           // The IP/host of the device running your MQTT broker

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
const int publishInterval = 1000; // Publish potentiometer value ever x millisec


const int potPin = A0;            // Pin of connected analog potentiometer
int val = 0;                      // Store value for potentiometer (0-1023)
float conversion = 1024/180;      // Servo needs to receive values in degrees - this servo rotates 180 degrees
int servoVal = 0;                 // Store value from potentiomenter to publish to servo
//int oldServoVal = 0;            // Only needed if you want to publish message on potentiometer change

void setup() {
  Serial.begin(115200);                // Default ESP8266 baud rate
  setup_wifi();
  client.setServer(mqtt_server, 1883); // Default MQTT port
  client.setCallback(callback);        // Function to be called when message on subscribed topic is received
}


void setup_wifi() {
  delay(10);
  
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  // Connect to a WiFi network
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  /*
   * This device does not subscribe to any messages, thus this function can be empty
   */

}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client Potentiometer")) {
      Serial.println("Connected to MQTT Broker at " + (String) mqtt_server);
      // Once connected, publish a test message
      client.publish("test", "hello broker");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {
  val = analogRead(potPin);     // Read potentiometer value (0-1023)
  servoVal = val/conversion;    // Convert value to degrees (0-180)
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > publishInterval) {
    lastMsg = now;
    snprintf (msg, 75, "%ld", servoVal);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("servo", msg);
  }

  /*  Alternatively, instead of sending a value every x millisec,
   *  you can send a value on change. Though this may cause a slight
   *  hiccup, as your device will publish A LOT of data.

  if (servoVal != oldServoVal) {
    lastMsg = now;
    snprintf (msg, 75, "%ld", servoVal);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("servo", msg);
    oldServoVal = servoVal;
  }
  
  */
}
