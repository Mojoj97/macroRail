
#include <Arduino.h>
#include "A4988.h"
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 34;  // the number of the pushbutton pin
const int ledPin = 21;    // the number of the LED pin
int Step = 12; //GPIO14---D5 of Nodemcu--Step of stepper motor driver
int Dire  = 13; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver
int Sleep = 14; //GPIO12---D6 of Nodemcu-Control Sleep Mode on A4988
int MS1 = 15; //GPIO13---D7 of Nodemcu--MS1 for A4988
int MS2 = 27; //GPIO16---D0 of Nodemcu--MS2 for A4988
int MS3 = 26; //GPIO15---D8 of Nodemcu--MS3 for A4988

 
// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
//Motor Specs
const int spr = 200; //Steps per revolution
int RPM = 100; //Motor Speed in revolutions per minute
int Microsteps = 1; //Stepsize (1 for full steps, 2 for half steps, 4 for quarter steps, etc)
//Providing parameters for motor control
A4988 stepper(spr, Dire, Step, MS1, MS2, MS3);
 

void setup() {
  Serial.begin(9600);
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dire,  OUTPUT); //Direcction pin as output
  pinMode(Sleep,  OUTPUT); //Set Sleep OUTPUT Control button as output
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dire, LOW);
  
  // Set target motor RPM to and microstepping setting
  stepper.begin(RPM, Microsteps);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    for(int i = 0; i < 10; i++ ){
      rotate(Sleep, 360);
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}

void rotate(int sleepPin, int rotationDegree){
  digitalWrite(sleepPin, HIGH); //A logic high allows normal operation of the A4988 by removing from sleep
  stepper.rotate(rotationDegree);
  digitalWrite(sleepPin, LOW);
  delay(1000);
}
