/**
 * Based on "Basic ESP8266 MQTT example" by the PubSubClient library
 * 
 * The intention is to run this code on an ESP8266 with a servo connected,
 * and use the potentiometer on another ESP8266 to control the servo using MQTT.
 * Use the 'mqtt_potentiometer' code for the other device.
 * 
 * It listens to the topic 'servo' and rotates the servo based on the potentiometer
 */


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h> 

// Change these to values suitable for your network
const char* ssid = "LAN Solo";                   // Wi-Fi name
const char* password = "EmpireDidNothingWrong";  // Wi-Fi password
const char* mqtt_server = "127.0.0.1";           // The IP/host of the device running your MQTT broker

Servo myservo;
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];

void setup() {
  myservo.attach(D5);                  // Set your servo to desired pin
  myservo.write(0);                    // Set servo to mid-point
  
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

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());
}

/**
 * This function is only invoked when you receive messages on a subscribed topic
 */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  
  // Convert payload from byte* to string
  String rec = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
    rec += (char) payload[i];
  }
  Serial.println();

  // Change position on servo according to received integer
  // Conversion to degrees is done on publishing device
  myservo.write(rec.toInt());

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...\n");
    // Attempt to connect
    if (client.connect("ESP8266Client servo")) {
      Serial.println("Connected to MQTT Broker at " + (String) mqtt_server);
      
      // Subscribe to topic 'servo'
      client.subscribe("servo");
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
   * This is where we publish message to the MQTT broker
   * Since this device will only receive data, this is empty
   */
}
