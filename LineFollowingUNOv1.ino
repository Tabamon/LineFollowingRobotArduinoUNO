//Line following robot code Arduino UNO

#include <Servo.h>
#define defaultSpeed 9
#define steerSpeed 12
#define gentleSteerSpeed 10
#define turnOnSwitch 12


enum Sensors{
  left=4, midLeft, central, midRight, right
};

Servo leftMotor, rightMotor;
int lastIRRecord;
bool noIRActive();

void setup() {
  leftMotor.attach(10);
  rightMotor.attach(11);
  leftMotor.write(0);
  rightMotor.write(0);
  pinMode(central,INPUT);
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  pinMode(midLeft,INPUT);
  pinMode(midRight,INPUT);
  pinMode(turnOnSwitch,INPUT);
  
}

void loop() {
  if (digitalRead(turnOnSwitch)==HIGH){
    if (digitalRead(central)==HIGH){
      leftMotor.write(defaultSpeed);
      rightMotor.write(defaultSpeed);
      delay(150);
    }
    if (digitalRead(midLeft)==HIGH){
      rightMotor.write(gentleSteerSpeed);
      delay(150);
    }
    if (digitalRead(midRight)==HIGH){
      leftMotor.write(gentleSteerSpeed);
      delay(150);
    }
    if(digitalRead(left)==HIGH){
      rightMotor.write(steerSpeed);
      delay(150);
      lastIRRecord=left;
    }
    if(digitalRead(right)==LOW){
      leftMotor.write(steerSpeed);
      delay(150);
      lastIRRecord=right;
    }
    if (noIRActive()){
      switch (lastIRRecord){
        case left:
          rightMotor.write(steerSpeed);
          delay(150);
        break;
        case right:
          leftMotor.write(steerSpeed);
          delay(150);
        break;
        default:
          //nothing
        break;
      }
    }
  }
}

bool noIRActive(){
  bool flag = true;
  for (unsigned i =left; i<right; ++i){
    if (digitalRead(i)==HIGH) flag = false;
  }
  return flag;
}
