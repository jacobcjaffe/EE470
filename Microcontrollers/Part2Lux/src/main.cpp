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
  V1: Simply outputs the read value from A0. x
  V2: Fully functional system according to the requirements.

File Dependencies: None
*/

#include <Arduino.h>
#include <cmath> // for use of e in the conversion of the adc value to the actual lux

// outputs
#define red D1
#define green D2
#define blue D3
#define buzzer D4

// input
#define pr A0
// functions
void RGBout(int, int, int);

// global variables
int luxVal;
int threshold = 0;
float luxCalc;
int redVal = 0;
int blueVal = 0;
int greenVal = 0;
char buffer[20];

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
  luxCalc = 2919 * pow(M_E, (float)luxVal * -.015782);
  dtostrf(luxCalc, 4, 3, buffer);
  Serial.println(buffer);
  //Serial.println("integer lux value: " + String(luxVal));
  if(Serial.availableForWrite()) {
    String msg = Serial.readStringUntil('\n');
    // if B is input from serial, buzz for 5 seconds
    if (msg[0] == 'B') {
      digitalWrite(buzzer, 1);
      delay(5000);
      digitalWrite(buzzer, 0);
    }

  }
  // vary intensity of red in the LED with the lux over 150 
  if (luxCalc > 150) {
    digitalWrite(buzzer, 0);
    redVal = (int)(255 * (luxCalc / 700));
    // clamp red value to 255
    if (redVal > 255) {
      redVal = 255;
    }
    greenVal = 255 - redVal;
    blueVal = 255 - redVal;
    RGBout(redVal, blueVal, greenVal);
  }
  else { // if lux is below 300, display white LED and play buzzer.
    digitalWrite(buzzer, 1);
    RGBout(255, 255, 255);
  }
  //delay(1500);
}


// a function to control the RGB LED module. The analog write uses a PWM signal to control
// the color of the LED. 
void RGBout(int redVal, int blueVal, int greenVal) {
  analogWrite(red, redVal);
  analogWrite(blue, blueVal);
  analogWrite(green, greenVal);
}