#include "sensor.h"
#include <dht.h>

// setup sensor
Sensor::Sensor(int switch1, int switch2, int temp, int hum) {
    s1 = switch1;
    s2 = switch2;
    tempPin = temp;
    humPin = hum;
    dht = new DHT(tempPin, DHT11);
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    pinMode(tempPin, INPUT);
    pinMode(humPin, INPUT);
    Serial.println(digitalRead(s1));
    Serial.println(digitalRead(s2));
}

// method to await one of the switch pins to turn high
int Sensor::WaitSwitch() {
    while(1) {
        if (digitalRead(s1)) {
            node = 1;
            Serial.println("Switch 1 was pressed!");
            return 1;
        }
        else if (digitalRead(s2)) {
            node = 2;
            Serial.println("Switch 2 was pressed!");
            return 2;
        }
        delay(30); // small delay
    }
}

void Sensor::GetTemp() {
    Serial.println("Reading temperature and humidity...");
    delay(1000);
    temp = dht->readTemperature(false, true);
    hum = dht->readHumidity();
    Serial.print("Node: ");
    Serial.println(node);
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" degrees Celsius");
    Serial.print("Humidity: ");
    Serial.println(hum);
}