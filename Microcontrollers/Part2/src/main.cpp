#include <Arduino.h>
#define outPin D1
// put function declarations here:
int myFunction(int, int);
int ms = 2400;
bool on;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    String rx = Serial.readStringUntil('\n');
    // if A is sent, blink LED faster, can't be less than 0 ms. 
    if (rx[0] == 'A') {
      if (ms > 0) {
        ms -= 300;
      }
    }
    // else if B is sent, blink LED slower
    else if (rx[0] == 'B') {
      ms += 300;
    }
  }
  digitalWrite(outPin, on);
  // print status of LED
  if (on) {Serial.println("LED is on");}
  else {Serial.println("LED is off");}
  Serial.println("delay: " + String(ms));
  on = !on;
  delay(ms);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}