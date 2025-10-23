#include <Arduino.h>
#include "Internet.h"
#include "sensor.h"

// use a singleton of the internet class for all internet related methods
Internet* net;

Sensor* s;
void setup() {
  SetupWifi();
  // setup a new instance of the internet class
  net = new Internet();
  String str = net->GetDateTime();
  // setup a new instance of the sensor class
  s = new Sensor(D0, D1, A0, A0);
}

void loop() {
  s->WaitSwitch();
  s->GetTemp();
  net->PushData(s->node, s->temp, s->hum);
}
