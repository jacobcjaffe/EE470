#include "sensor.h"
#include <dht.h>

// setup sensor
Sensor::Sensor(int switch1, int switch2, int temp, int hum) {
    s1 = switch1;
    s2 = switch2;
    tempPin = temp;
    humPin = hum;
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
            return 1;
        }
        else if (digitalRead(s2)) {
            node = 2;
            return 2;
        }
        delay(20);
    }
}

void Sensor::GetTemp() {
    DHT dht(A0, DHT11, 1);
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    Serial.println(temp);
    Serial.println(hum);
}