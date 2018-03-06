/**
 * Based on "Basic ESP8266 MQTT example" by the PubSubClient library
 * 
 * Use this code to control LEDs on an ESP board using MQTT. Used in
 * this example is the built-in LED and 4 connected lEDs through pins.
 * Use your teminal (or another device) to publish messages to the MQTT
 * broker, which forwards it to the device running this code.
 *
 * This ecample subscribes to the topic 'led' and changes the state of LEDs 
 * based on receiving values in topic, 0 for built-in LED and 1-4 for connected 
 * LEDs. All LEDs are initiated with their lights off. Sending message '2'
 * to topic 'led' makes led2 turn on, and sending '2' again makes it turn
 * off. You can also use messages 'on' and 'off' to control all the lights.
 * 
 */


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BUILTIN_LED 2 // Built-in LED on the ESP8266 board

// Pins of LEDs connected to your board
const int led1 = D5;
const int led2 = D6;
const int led3 = D7;
const int led4 = D8;

// Change these to values suitable for your network
const char* ssid = "LAN Solo";                  // Wi-Fi name
const char* password = "EmpireDidNothingWrong"; // Wi-Fi password
const char* mqtt_server = "127.0.0.1";          // The IP/host of the device running your MQTT broker

WiFiClient espClient; 
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);         // Initialize LEDs as output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(115200);                 // Default ESP8266 baud rate
  setup_wifi();
  client.setServer(mqtt_server, 1883);  // Default MQTT port
  client.setCallback(callback);         // Function to be called when message on subscribed topic is received
  digitalWrite(BUILTIN_LED, HIGH);      // BUILTIN_LED has active LOW
}


void setup_wifi() {
  delay(10);

  Serial.print("Connecting to ");
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
  Serial.print("] ");

  // Convert payload from byte* to string
  String rec = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    rec += (char) payload[i];
  }
  Serial.println();

  if ((char)payload[0] == '0') {
    Serial.println("Change state of built-in LED");
    digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));   
  } else if ((char)payload[0] == '1') {
    Serial.println("Change state of LED1");
    digitalWrite(led1, !digitalRead(led1));
  } else if ((char)payload[0] == '2') {
    Serial.println("Change state of LED2");
    digitalWrite(led2, !digitalRead(led2));
  } else if ((char)payload[0] == '3') {
    Serial.println("Change state of LED3");
    digitalWrite(led3, !digitalRead(led3));
  } else if ((char)payload[0] == '4') {
    Serial.println("Change state of LED4");
    digitalWrite(led4, !digitalRead(led4));
  } else if (rec == 'on') {
    Serial.println("Change state of LED: ALL ON");
    digitalWrite(BUILTIN_LED, LOW);   // Built-in LED has active LOW
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  } else if (rec == 'off') {
    Serial.println("Change state of LED: ALL OFF");
    digitalWrite(BUILTIN_LED, HIGH);  // Built-in LED has active LOW
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client LED")) {
      Serial.println("Connected to MQTT Broker at " + (String) mqtt_server);
      // Subscribe to topic 'LED'
      client.subscribe("led");
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

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

 /*
  *  This device does not publish any data 
  */
}
