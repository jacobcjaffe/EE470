#include "Internet.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void SetupWifi() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  const char* ssid = "cringelord";
  const char* password = "cuddlesishorrible";
  Serial.println("Connecting to Wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.println(".");
  }
  Serial.println("Connected");    
};

Internet::Internet() {
    client.setInsecure();
    // display some connection details
    Serial.println("Wifi Connected!");
    Serial.println("----------------------");
    Serial.println("Connected to: " + WiFi.SSID());
    Serial.println("MAC: " + WiFi.macAddress());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

String Internet::GetDateTime() {
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();
    Serial.println("trying to get datetime");
    const char* url = "https://timeapi.io/api/time/current/zone?timeZone=America%2FLos_Angeles";
    if(http.begin(client, url)) {
        Serial.println("[http] connection successful");
    }
    else {
        Serial.println("[http] unable to connect");
        return "";
    }
    int code = http.GET();
    if (code == HTTP_CODE_OK) {
        Serial.println(http.getString());
        return http.getString();
    }
    else {
        Serial.println("couldn't get datetime...");
        Serial.println("Code: " + http.errorToString(code));
        return "";
    }
}

void Internet::PushData(int node, float temp, float hum) {
    HTTPClient http;
    WiFiClientSecure client;
    String datetime = GetDateTime();
    client.setInsecure();
    String url = "https://darkred-trout-902385.hostingersite.com/ESP_assignment/insertdata.php?";
    String nodeurl;
    if (node == 1) {
        nodeurl = "node_name=node_1&";
    }
    else if (node == 2) {
        nodeurl = "node_name=node_2&";
    }
    else {
        Serial.println("Invalid node name!");
    }

    String tempurl = "temperature=" + String(temp) + "&";
    String humurl = "humidity=" + String(hum) + "&";
    String timeurl = "time_received=" + datetime;
    String fullurl = url + nodeurl + tempurl + humurl + timeurl;
    if(http.begin(client, fullurl)) {
        Serial.println("[http] connection successful");
    }
    else {
        Serial.println("[http] unable to connect");
        return;
    }
    int code = http.GET();
    if (code == HTTP_CODE_OK) {
        Serial.println(http.getString());
    }
    else {
        Serial.println("couldn't push data to database...");
    }
}