/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
#include <Arduino.h>
#include <TM1637Display.h>
#include "Mouse.h"

// Pins defined for 7 segment display library
#define CLK 18
#define DIO 19


//Pins defined for the sonar sensor
int trigPin = 21;    // Trigger
int echoPin = 20;    // Echo
long duration, inches;

//Create display object with defined paramaters
TM1637Display display(CLK, DIO);
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);//setup the sonar pin to be an output
  pinMode(echoPin, INPUT);//setup the sonar pin to be an output
  Mouse.begin();//start the mouse
}
 
void loop() {
 

  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x0f);
 
 
}

int getInches() {
  long duration, inches;
   // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  Serial.print("in: ");
  Serial.println(inches);
  return inches;
}

void MoveMouse(int loops) {
  Serial.print("Moving the Mouse ");
  Serial.print(loops);
  Serial.println(" times");
  for (;loops >=0; loops--) {
    Mouse.move(20, 0, 0);
    Mouse.move(0, -20, 0);
    Mouse.move(-20, 0, 0);
    Mouse.move(0, -20, 0);
    }
  Serial.println("Done moving the mouse");
}
