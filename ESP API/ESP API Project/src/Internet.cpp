#include "Internet.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


void SetupWifi() {
  const char* ssid = "iPhone (4)";
  const char* password = "eeatssu470";
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

// a method to send a message using iftt with a given payload
void Internet::SendMessage(String msg) {
    DynamicJsonDocument doc(1024);
    // if a message was included
    if (!msg.isEmpty()) {
        doc["message"] = msg;
    }

    String payload;
    serializeJson(doc, payload);

    HTTPClient http;
    if(http.begin(client, ifftAddr)) {
        Serial.println("[http] connection successful");
        http.addHeader("Content-Type", "application/Json");
    }
    else {
        Serial.println("[http] unable to connect");
        http.end();
        return;
    }
    int code = http.POST(payload);
    if (code == HTTP_CODE_OK) {
        Serial.println("[http] succesfully posted");
        Serial.println(http.getString());
    }
    else {
        Serial.println("[http] could not post...");
        Serial.println("[http] Error: " + http.errorToString(code));
    }
    http.end();
}

// a method to get the status of the led by using http GET to get the contents of results.txt
int Internet::GetLED() {
    // start http client on the path to the results.txt for the led addr
    HTTPClient http;
    if(http.begin(client, ledAddr)) {
        Serial.println("[http] connection to led results.txt successful");
    }
    else {
        Serial.println("[http] connection on led results.txt failed");
        http.end();
        return OFF;
    }

    // use the get method to get the data in results.txt
    int code = http.GET();
    if (code == HTTP_CODE_OK) {
        Serial.println("[http] led get successful");
        String payload = http.getString();
        Serial.print("file content: ");
        Serial.println(payload);

        // parse payload
        if (payload == "on") {
            Serial.println("LED ON");
            http.end();
            return ON;
        }
        else if (payload == "off") {
            Serial.println("LED OFF");
            http.end();
            return OFF;
        }
        else {
            Serial.println("[http] unable to parse led results.txt");
            http.end();
            return OFF;
        }
    }
    else {
        Serial.println("[http] could not get led results.txt");
        Serial.println("[http] Error: " + http.errorToString(code));
        http.end();
        return OFF;
    }
}

// a method for controlling the led once the led status has been confirmed.
// it will query for the led values if the led is on
void Internet::ToggleLED(int status) {

    if (status == OFF) {
        Serial.println("[led] turning LED off");
        digitalWrite(LEDr, 0);
        digitalWrite(LEDg, 0);
        digitalWrite(LEDb, 0);
    }
    else {
        Serial.println("[led] turning led on");
        Serial.println("[led] getting rgb values");
        this->GetRGB();
    }
}

// performs an http request to get the values for r, g, and b. It will set the 
// r, g, and b values using pwm
void Internet::GetRGB() {
    analogWrite(LEDr, 10);
    analogWrite(LEDg, 200);
    analogWrite(LEDb, 80);
     // start http client on the path to the results.txt for the led addr
    HTTPClient http;
    if(http.begin(client, rgbAddr)) {
        Serial.println("[http] connection to rgb results.txt successful");
    }
    else {
        Serial.println("[http] connection on rgb results.txt failed");
        http.end();
        return;
    }

    // use the get method to get the data in results.txt
    int code = http.GET();
    if (code == HTTP_CODE_OK) {
        Serial.println("[http] led get rgb successful");
        String payload = http.getString();
        Serial.print("file content: ");
        Serial.println(payload);
        String vals[3];
        int r, g, b;
        int prevIdx = 0;
        int count = 0;
        // split and parse the string by delimiter ','
        for(int i = 0; i < payload.length(); i++) {
            if (payload[i] == ',') {
                Serial.print("found delimiter at " );
                Serial.println(i);
                vals[count] = payload.substring(prevIdx, i);
                prevIdx = i+1;
                count++;
            }
        }
        Serial.println(".....");
        Serial.println(prevIdx);
        Serial.println(payload.length()-1);
        Serial.println(".....");
        vals[2] = payload.substring(prevIdx, payload.length());
        for(int i = 0; i < 3; i++) {
            Serial.println(vals[i]);
        }
        r = vals[0].toInt();
        g = vals[1].toInt();
        b = vals[2].toInt();
        analogWrite(LEDr, r);
        analogWrite(LEDg, g);
        analogWrite(LEDb, b);
    }
    else {
        Serial.println("[http] could not get rgb results.txt");
        Serial.println("[http] Error: " + http.errorToString(code));
        http.end();
        return;
    }
}