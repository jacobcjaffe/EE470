//-----------------------------
// Title: MQTT Assignment
//-----------------------------
// Program Details
//-----------------------------
// Purpose: Conenct to broker.mqtt-dashboard.com, publish the status of the switch when the 
//     switch changes values, publish volts from the wiper of the potentiometer every 10 seconds,
//     and subscribe to a topic to change the status of an LED. 
// Dependencies: Make sure you have installed PubSubClient.h
// Compiler: PlatformIO version 6.1.19
// Author: Jacob Jaffe
// OUTPUT: publishes the volts at the wiper of the potentiometer read from A0 with message format "volts: (volts to 2 decimal places)"
//    Additionally publishes a "0" or "1" for the output of the switch on D0. Also outputs the binary value received for the LED.
//    on GPIO pin D1.      
// INPUT: Received value from the broker to update the output of the LED.
// SETUP: To see the published values go to http://www.hivemq.com/demos/websocket-client/ 
//        subscribe to inTopic and outTopic.
// Versions: 
//  v1: Nov-25-2025: It all works
//-----------------------------

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>

#define SWITCH D0
#define LED D1
#define POT A0

// WiFi variables
const char* ssid = "iPhone (4)";  // Enter your WiFi name
const char* password = "eeatssu470";  // Enter WiFi password

// MQTT variables
const char* mqtt_server = "broker.mqtt-dashboard.com";
// out topics where ESP publishes
const char* POTTopic = "testtopic/temp/outTopic/pot";
const char* SWITCHTopic = "testtopic/temp/outTopic/switch";
const char* subscribeTopic = "testtopic/temp/inTopic";  // inTopic where ESP has subscribed to
#define publishTimeInterval 10000 // in seconds 

// Definitions 
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
#define BUILTIN_LED 2 // built-in LED
char msg[MSG_BUFFER_SIZE];
int value = 0;

WiFiClient espClient;
PubSubClient client(espClient); // define MQTTClient 


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
  //------------------------------------------

void callback(char* topic, byte* payload, int length) {
  Serial.print("Message arrived ["); // Received the incoming message
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);  // the received value is in (char)payload[i]
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED, 1);
  }
  else if ((char)payload[0] == '0') {
    digitalWrite(LED, 0);
  }
}
  //------------------------------------------

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 //------------------------------------------

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(POT, INPUT);
  pinMode(SWITCH, INPUT);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
//------------------------------------------
float volts;
void getPot() {
  volts = analogRead(POT) * 3.3 / 1023;
}
//------------------------------------------
bool switchPressed = false; // keeping track of last value of switch read
void loop() {

  if (!client.connected()) {
    reconnect(); // check for the latest value in inTopic 
  }
  client.loop();

  if (digitalRead(SWITCH)) {
    // if switch is being held down, no need to publish again
    if (!switchPressed) {
      snprintf(msg, MSG_BUFFER_SIZE, "1");
      Serial.println("Switch has been pressed");
      client.publish(SWITCHTopic, msg);
    }
    switchPressed = true;
  }
  else { // switch is off
    // only need to publish when switch changes from 1 to 0
    if (switchPressed) {
      snprintf(msg, MSG_BUFFER_SIZE, "0");
      Serial.println("Switch has been pressed");
      client.publish(SWITCHTopic, msg);      
    }
    switchPressed = false;
  }

  // Publish to POTTopic every 10 seconds, recording the voltage
  unsigned long now = millis(); 
  if (now - lastMsg > publishTimeInterval) {
    lastMsg = now;
    getPot();
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "volts: %.2f", volts); // prints Number # 1, Number # 2, .....
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(POTTopic, msg);
  }
}