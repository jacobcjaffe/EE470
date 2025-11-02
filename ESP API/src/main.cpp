#include <Arduino.h>
#include "Internet.h"
#include "sensor.h"

// use a singleton of the internet class for all internet related methods
Internet* net;

void setup() {

  // set up wifi with ssid and password
  SetupWifi();
  // setup a new instance of the internet class
  net = new Internet();
}

void loop() {
  delay(5000); // wait at least 5 seconds until the next input
}
