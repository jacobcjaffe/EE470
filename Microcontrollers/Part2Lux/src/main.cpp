/*
Title: Lux Meter Assignment
-----------------------------------------------------
Program Details: The microcontroller is connected to the photoresistor in series with a resistor, 
  which acts as a voltage divider. The microcontroller looks at that value, and it will play a buzzer and
  display white on an LED if the value is above a threshold (meaning the lux present is low).
  If it's below that threshold, it will turn off the buzzer and turn the LED red, and as it goes further below
  that threshold, the intensity of the red will increase. 
Inputs: A0 - the analog input that takes the voltage from the photoresistor in series with another resistor.
OutputS: D1 - controls the red value of the RGB LED with PWM
        D2 - controls the green value of the RGB LED with PWM
        D3 - controls the blue value of the RGB LED with PWM
        D4 - controls the buzzer with a digital output
Date: September 28, 2025
Compiler: SCons Build Framework (uses GCC) with PlatformIO
Versions: 
  V1: Simply outputs the read value from A0. 
*/

#include <Arduino.h>
#define red D1
#define green D2
#define blue D3
#define buzzer D4
#define pr A0
// functions
int myFunction(int, int);
void RGBout(int, int, int);

// global variables
int luxVal;
int threshold = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pr, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  luxVal = analogRead(pr);
  Serial.println(luxVal);
  if (luxVal > threshold) {

  }
  else {

  }
  delay(1500);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

// a function to control the RGB LED module. The analog write uses a PWM signal to control
// the color of the LED. 
void RGBout(int redVal, int blueVal, int greenVal) {
  analogWrite(red, redVal);
  analogWrite(blue, blueVal);
  analogWrite(green, greenVal);
}