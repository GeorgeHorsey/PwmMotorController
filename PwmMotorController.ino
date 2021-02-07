/*
 * Developed by George Horsey
 * www.georgehorsey.com
 * Date of Creation: 02.06.2021
 * Date of Last Edit: 02.06.2021
 * 
 * Motor controller for FIRST Robotics. 
 * Values are entered from the Serial Monitor. 
 * Start with either an l or r to denote which motor 
 * controller you want to control after that 
 * enter a number at or between -100 to 100
 * Then press enter. 
 * This will send the command through a map 
 * that will correct the percentage you entered
 * into Microseconds needed for PWM control of the
 * motor controllers. 
 */
 
#include <Servo.h> // needed to output microseconds to PWM motor controllers

Servo LeftMotorController;
Servo RightMotorController;

String MotorControllerInput = "0"; // used to hold initial value sent by user from Serial Monitor. 

// Used to check input string and decide which controller to send value to. 
const String LeftMotorLetter = "l"; // its an L not a one. 
const String RightMotorLetter = "r";

int MotorControllerInt = 0; // holds the value of speed after MotorControllerLetter is removed. 
int CorrectedPwmSignal = 0; // used to hold the output of the microseconds from map below. 

void setup() {
  Serial.begin(115200); // starting serial on arduino. 
  Serial.println("Ready!"); // print to serial to show that arduino has booted and is ready!

  pinMode (13, OUTPUT); //black wire
  pinMode (12, OUTPUT); // red wire
  pinMode (11, OUTPUT); // white wire (PWM)

  pinMode (10, OUTPUT); // white wire (PWM)
  pinMode (9, OUTPUT); // red wire
  pinMode (8, OUTPUT); //black wire

  digitalWrite (13, 0); // ground pin
  digitalWrite (12, 1); // power pin
  digitalWrite (11, 1); // pwm pin

  digitalWrite (10, 1); // pwm pin
  digitalWrite (9, 1); // power pin
  digitalWrite (8, 0); // ground pin

  // tells which pin to send microseconds to. 
  LeftMotorController.attach(11); 
  RightMotorController.attach(10); 
}

void loop() {
  if (Serial.available() > 0){
    MotorControllerInput = Serial.readString(); // reads the string sent by user. 
  }
  if (MotorControllerInput.startsWith(LeftMotorLetter)){ // decides if string sent by user starts with L. 
    MotorControllerInput.remove(0, 1); // removes the letter getting ready to create integer value.
    MotorControllerInt = MotorControllerInput.toInt(); // created int from string.
    CorrectedPwmSignal = map(MotorControllerInt, -100, 100, 800, 2200); // map to change percent to microseconds. 
    LeftMotorController.writeMicroseconds(CorrectedPwmSignal); // send microseconds to controller. 
  }
  else if (MotorControllerInput.startsWith(RightMotorLetter)) { // decides if string sent by user starts with R. 
    MotorControllerInput.remove(0, 1); // removes the letter getting ready to create integer value.
    MotorControllerInt = MotorControllerInput.toInt(); // created int from string.
    CorrectedPwmSignal = map(MotorControllerInt, -100, 100, 800, 2200); // map to change percent to microseconds. 
    RightMotorController.writeMicroseconds(CorrectedPwmSignal); // send microseconds to controller. 
  }
}
