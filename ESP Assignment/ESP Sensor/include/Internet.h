#ifndef INTERNET_H
#define INTERNET_H

#include <Arduino.h>
#include <ESP8266Wifi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

void SetupWifi();

// a class to encapsulate all internet and http requests
class Internet {
public:
    Internet();
    String GetDateTime();
    void PushData(int node, float temp, float hum);
private:
    WiFiClientSecure client;
    HTTPClient http;
};

#endif