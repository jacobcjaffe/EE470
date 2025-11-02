/*
Program: ESP API and Remote Control
Author: Jacob Jaffe
Date: 11/2/2025
Description: This program will use a switch digital input, and if it's high, it will send an api request to IFTTT, which will
then send a message to my phone. It will also use my hosted website on Hostinger, and query two txt files, results.txt and rgb.txt. 
results.txt contains a value of whether the rgb led should be on or not, and rgb contains the r, g, and b values for the pwm output
from the ESP8266. 
Input: D0 - switch input
Output: D1 - LED red value (pwm), D2 - LED green value (pwm), and D3 - LED blue value (pwm)
Compiled: PlatformIO (GCC)
Dependencies: Arduino.h, ESP8266Wifi, ESP8266HTTPClient, and ArduinoJson
Notes: 
    - finished the program
*/

#include <Arduino.h>
#include "Internet.h"

#define sw1 D0

unsigned long currentMillis;
Internet* net;
int ledStatus;

void setup() {
  Serial.begin(9600);
  // set up wifi with ssid and passwordd
  SetupWifi();
  net = new Internet();
  pinMode(sw1, INPUT);
  pinMode(LEDr, OUTPUT);
  pinMode(LEDb, OUTPUT);
  pinMode(LEDg, OUTPUT);
  int status = net->GetLED();
  net->ToggleLED(status);
}

void loop() {
  if (digitalRead(sw1)) {
    net->SendMessage("this is a test message...");
    delay(100);
  }
  currentMillis = millis();
  if (currentMillis - net->previousMillis >= net->interval) {
    net->previousMillis = currentMillis;
    Serial.println("two minutes have passed");
    ledStatus = net->GetLED();
    net->ToggleLED(ledStatus);
  }
}