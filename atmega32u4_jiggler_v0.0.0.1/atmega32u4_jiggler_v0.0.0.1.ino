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


//Timing variables
unsigned long moveTimer;
unsigned long moveTimerTotal = 0;



// Pins defined for 7 segment display library
#define CLK 18
#define DIO 19
//Create display object with defined paramaters
TM1637Display display(CLK, DIO);


//Pins defined for the sonar sensor
int trigPin = 21;    // Trigger
int echoPin = 20;    // Echo
long duration, inches;

//Variables for the pot
int sensorPin = 10;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int outputValue = 0; // value for pot to minutes map
int minutes = 0;// minutes to wait before moving the mouse
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);//setup the sonar pin to be an output
  pinMode(echoPin, INPUT);//setup the sonar pin to be an output
  Mouse.begin();//start the mouse
}
 
void loop() {
  //shit for the display, not sure how often I actually need to call this
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x0f);
  inches = getInches();
  UpdateDisplay(inches);
  minutes = Timer();
  if ((millis()-moveTimerTotal) > ((minutes*60*1000)-30000)){
    ThirtySecondMouseTimer();
    Serial.println("We hit the countdown for 30 seconds code");
  }
  Serial.println();
  Serial.print(millis());
  Serial.print(" - ");
  Serial.print((minutes*60*1000)-30000);
  Serial.print(" = ");
  Serial.print(millis()-((minutes*60*1000)-30000));
  Serial.println("");
  
  
  
}

long getInches() {
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

void UpdateDisplay(int nums){
  Serial.print("We're going to write: ");
  Serial.print(nums);
  Serial.println(" to the display");
  Serial.println("");
  display.showNumberDec(nums, false);
}

int Timer(){
  sensorValue = analogRead(sensorPin); // read the value from the sensor:
  outputValue = map(sensorValue, 0, 1023, 1, 45);
  Serial.print("Minutes to wait: ");
  Serial.println(outputValue);
  return outputValue;
}


void ThirtySecondMouseTimer(){
  Serial.println("Start of Thirty Second Timer?");
  for (int seconds = 30; seconds >= 0; seconds--){
    UpdateDisplay(seconds);
    Serial.print("mills passing every seconds is equal to: ");
    Serial.println(millis());
    delay(1000);
    Serial.print("seconds left on timer: ");
    Serial.println(seconds);
    Serial.println("");
    if (seconds = 0){
      Serial.println("Seconds = zero");
      int moveInches = getInches();
      if (moveInches <=8){
        Serial.println("Something is within 8 inches");
        MoveMouse(5);
        moveTimerTotal = millis();
      }
      
    }
  }
}
