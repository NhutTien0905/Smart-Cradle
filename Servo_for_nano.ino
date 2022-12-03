#define SERVO1_PIN  6 // D5
#define START 5
#define DeC1 7
#define DeC2 8
#include <Arduino.h>
#define DISABLE_COMPLEX_FUNCTIONS     // Activating this disables the SINE, CIRCULAR, BACK, ELASTIC, BOUNCE and PRECISION easings. Saves up to 1850 bytes program memory.
#define MAX_EASING_SERVOS 1
#define ENABLE_EASE_QUADRATIC //
#define ENABLE_EASE_CUBIC //
#define ENABLE_EASE_QUARTIC //
#define ENABLE_EASE_SINE //
#define ENABLE_EASE_CIRCULAR//
#define ENABLE_EASE_BACK //
#define ENABLE_EASE_ELASTIC //
#define ENABLE_EASE_BOUNCE //
#define ENABLE_EASE_PRECISION //
#define ENABLE_EASE_USER

#include "ServoEasing.hpp"

ServoEasing Servo1;

#define START_DEGREE_VALUE  90  // The degree value written to the servo at time of attach.

int speedRotate_A= 50;
int speedRotate_B=50;
int speedRotate_C= 50;
int speedRotate_D=50;
char servoMode='A';
bool state = 0;
void setup() {
   Serial.begin(115200);
   if (Servo1.attach(SERVO1_PIN, START_DEGREE_VALUE) == INVALID_SERVO) {
        Serial.println(F("Error attaching servo"));
        while (true) {
        }
    }
    delay(500);
  // put your setup code here, to run once:
   pinMode(DeC1, INPUT);
   pinMode(DeC2, INPUT);
   pinMode(START,INPUT);
}


void runningServo()
{
  
    Serial.println(F("Move to 180 degree with 15 degree per second using interrupts and switch LED on at 120 degree"));

    Servo1.startEaseTo(120, 50, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() < 120) {
        delay(20); // just wait until angle is above 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

    delay(100);
       Servo1.startEaseTo(30, 50, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() > 30) {
        delay(20); // just wait until angle is below 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

    delay(100);
}
void ModeA()
{
      Servo1.setEasingType(EASE_LINEAR);
      Servo1.startEaseTo(120,  speedRotate_A, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() < 120) {
        delay(20); // just wait until angle is above 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

    delay(100);
       Servo1.startEaseTo(30,  speedRotate_A, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() > 30) {
        delay(20); // just wait until angle is below 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

    delay(100);
}
void ModeB()
{
      Servo1.setEasingType(EASE_BACK_OUT);
      Servo1.startEaseTo(105,  speedRotate_B, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() < 120) {
        delay(20); // just wait until angle is above 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

    delay(100);
       Servo1.startEaseTo(45,  speedRotate_B, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() > 30) {
        delay(20); // just wait until angle is below 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

    delay(100);
}
void ModeC()
{
    Servo1.setEasingType(EASE_LINEAR);
      Servo1.startEaseTo(START_DEGREE_VALUE,  speedRotate_A, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() < 120) {
        delay(20); // just wait until angle is above 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }
}
void ModeD()
{
      Servo1.setEasingType(EASE_SINE_OUT);
      Servo1.startEaseTo(120,  speedRotate_D, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() < 120) {
        delay(20); // just wait until angle is above 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

 
    Servo1.setEasingType(EASE_SINE_IN);
       Servo1.startEaseTo(90,  speedRotate_D, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() < 90) {
        delay(20); // just wait until angle is below 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }
    

    
       Servo1.setEasingType(EASE_SINE_OUT);
      Servo1.startEaseTo(30,  speedRotate_D, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() >30) {
        delay(20); // just wait until angle is above 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }

   
    Servo1.setEasingType(EASE_SINE_IN);
       Servo1.startEaseTo(90,  speedRotate_D, START_UPDATE_BY_INTERRUPT);
//    Servo1.startEaseTo(DEFAULT_MICROSECONDS_FOR_180_DEGREE, 50); // Alternatively you can specify the target as microsecond value
    while (Servo1.getCurrentAngle() > 90) {
        delay(20); // just wait until angle is below 120 degree
    }

    while (Servo1.isMoving()) {
        ; // wait for servo to stop
    }
    

}
void receiveMessage(){
  int DEC1=digitalRead(DeC1);
  int DEC2=digitalRead(DeC2);
  if ((DEC1==0)&&(DEC2==0)) {servoMode='A';}
  else if ((DEC1==0)&&(DEC2==1)) {servoMode='B';}
  else if ((DEC1==1)&&(DEC2==0)) {servoMode='C';}
  else if ((DEC1==1)&&(DEC2==1)) {servoMode='D';}
}
void loop() {
state = digitalRead(START);
Serial.println("Turn on");
if (state ==1){
  receiveMessage();
  if (servoMode=='A'){ModeA();}
  else if (servoMode=='B'){ModeB();}
  else if (servoMode=='C'){ModeC();}
  else if (servoMode=='D'){ModeD();}
  }
else{ModeC();}

}
