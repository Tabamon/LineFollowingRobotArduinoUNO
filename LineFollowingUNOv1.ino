//Line following robot code Arduino UNO

#include <Servo.h>
#define defaultSpeed 15 //pwm
#define steerSpeed 0 //pwm
#define gentleSteerSpeed 10 //pwm

#define turnOnSwitch 12 //pin

Servo leftMotor, rightMotor;

void setup() {
  leftMotor.attach(10);
  rightMotor.attach(11);
  leftMotor.write(0);
  rightMotor.write(0);
  DDRD = 0;
  Serial.begin(9600);
  pinMode(turnOnSwitch,INPUT_PULLUP);
  
}

void loop() {
  if (digitalRead(turnOnSwitch)==HIGH){
    byte IRArray = PIND; //values of pins of port D into IRArray
    IRArray = IRArray >> 2; //move the bits so that the leftmost sensor is in bit 0
//    IRArray = ~IRArray; //if doesnt work uncomment line
    IRArray = IRArray & 0x1f; //mask out unused bits
    Serial.println(IRArray);
    switch (IRArray){
      case 1: //leftmost sensor
      rightMotor.write(defaultSpeed);
      leftMotor.write(steerSpeed);
      break;
      case 2: //middle-left sensor
      rightMotor.write(defaultSpeed);
      leftMotor.write(gentleSteerSpeed);
      break;
      case 4: //middle sensor
      rightMotor.write(defaultSpeed);
      leftMotor.write(defaultSpeed);
      break;
      case 8: //middle-right sensor
      rightMotor.write(gentleSteerSpeed);
      leftMotor.write(defaultSpeed);
      break;
      case 16://rightmost sensor
      rightMotor.write(steerSpeed);
      leftMotor.write(defaultSpeed);
      break;
      default:
      // do nothing if multiple sensors are active or no sensors are active
      break;
    }
    delay(25); //give the arduino a chance to generate the waveform before changing again
  }
}
