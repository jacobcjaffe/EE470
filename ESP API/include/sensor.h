#include <Arduino.h>
#include <dht.h>

#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
    Sensor(int switch1, int switch2, int temp, int hum);
    int WaitSwitch();
    void GetTemp();
    void GetHumidity();
    float hum;
    float temp;
    int node;
private:
    int s1;
    int s2;
    int tempPin;
    int humPin;
    DHT* dht;
};

#endif