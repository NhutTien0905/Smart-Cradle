#include <NewPing.h>        

// L298N motor control pins
const int LeftMotorForward = 3;
const int LeftMotorBackward = 4;
const int RightMotorForward = 9;
const int RightMotorBackward = 10;

// sensor pins
#define trig_pin 2 // xac dinh chan trig
#define echo_pin_1 7 // xac dinh chan echo
#define echo_pin_2 8
#define echo_pin_3 12
#define echo_pin_4 13

#define maximum_distance 200

boolean goesForward = false;

int distance = 100;

int enable = 0;

//sensor function
#define SONAR_NUM 4
NewPing sonar[SONAR_NUM] = {
  NewPing(trig_pin, echo_pin_1, maximum_distance), // chan 7
  NewPing(trig_pin, echo_pin_2, maximum_distance), // chan 8 -> left
  NewPing(trig_pin, echo_pin_3, maximum_distance), // chan 12 
  NewPing(trig_pin, echo_pin_4, maximum_distance) // chan 13 -> right
};

int positions[4];


void setup(){
  Serial.begin(9600);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  delay(100);
  distances();
  delay(100);
}

void distances() {
  for (uint8_t i = 0;i<SONAR_NUM;i++){
    positions[i] = sonar[i].ping_cm();
  }
}



void moveStop(){
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}



void moveForward(){
  if(!goesForward){
    goesForward=true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}



void moveBackward(){
  goesForward=false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}



void turnRight(){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH); 
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(300);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}



void turnLeft(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(300);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
} 

void loop(){
  delay(50);
  int disForward = positions[0];
  int disBackward = positions[2];
  int disLeft = positions[1];
  int disRight = positions[3];
  
  while (Serial.available()){
    char key = Serial.read();
    if (key == 'Q'){ // auto run: turn right, traight 3000ms, turn right, traight 300ms, turn right, traight 100ms, stop
      if (disForward <= 15){
        moveStop();
        delay(300);
        moveBackward();
        delay(300);
        moveStop();
        delay(100);
        turnRight();
      }
      else{
        moveForward();
        delay(3000);
        turnRight();
        delay(100);
        moveForward();
        delay(300);
        turnRight();
        delay(100);
        moveForward();
        delay(200);
        moveStop();
      }  
      distances();
    }
    if (key == 'E'){ // control
      if (key == 'W'){
      enable = 0;
      moveForward();
      }
    
      else if (key == 'S'){
        moveBackward();
      }
      
      else if (key == 'A'){
        turnLeft();
      }
  
      else if (key == 'D'){
        turnRight();
      }
  
      else if (key == 'F'){
        enable = 1;
        moveStop();
      }
    } 
  }
}
