/*
Program: Internet.h
Author: Jacob Jaffe
Date: 11/2/2025
Description: The header file for the Internet class that handles the connection to WiFi, the http requests for 
the led (ON/OFF) and RGB values (0-255). It will also use a switch to send an api request to 
IFTTT to send a text to my phone.
Input: D0 - switch input
Output: D1 - LED red value (pwm), D2 - LED green value (pwm), and D3 - LED blue value (pwm)
Compiled: PlatformIO (GCC)
Dependencies: Arduino.h, ESP8266Wifi, ESP8266HTTPClient, and ArduinoJson
Notes: 
    - finished the program
*/

#ifndef INTERNET_H
#define INTERNET_H

#include <Arduino.h>
#include <ESP8266Wifi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define LEDr D1
#define LEDg D2
#define LEDb D3

void SetupWifi();

enum LED_STATUS {
    OFF = 0,
    ON = 1
};

// a class to encapsulate all internet and http requests
class Internet {
public:
    Internet();
    void SendMessage(String msg);
    // returns the status of the LED
    int GetLED();
    // gets the rgb values and uses pwm to write their values to the rgb
    void GetRGB();
    // toggles the led off, or if on, uses GetRGB
    void ToggleLED(int status);

    // values for creating a delay
    unsigned long previousMillis = 0;
    const unsigned long interval = 120000;
    /*
    String GetDateTime();
    void PushData(int node, float temp, float hum);
    */
private:
    WiFiClientSecure client;
    HTTPClient http;
    const char* ifftAddr = "https://maker.ifttt.com/trigger/esp_button_pressed/json/with/key/b_S8rR3mUMiGTOgUPZOC9p";
    const char* ledAddr = "https://jacobjaffe.io/API/results.txt";
    const char* rgbAddr = "https://jacobjaffe.io/API/rgb.txt";
};

#endif