/*
Title: Random Number Generator
---------------------------------------
Program Details:
Purpose: This programs tells the microcontroller to generate a random number every 5 seconds.
  It then sends that number over a serial connection at 9600 baud over the USB connection. It seeds
  the random number generator with an analog read from pin A0. 
Inputs: None
Ouptuts: A random number every 5 seconds
Date: September 28, 2025
Compiler: AVR-GCC with Arduino IDE 2.2.0
Author: Jacob Jaffe
Versions:
  V1: Program works and outputs the randomly generated number as expected.
*/

long randNum;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  randNum = random(0, 100);
  Serial.println(randNum);
  delay(5000);
}
