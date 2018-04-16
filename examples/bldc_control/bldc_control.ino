#include <Servo.h>

Servo bldc;

void setup() {
  Serial.begin(9600);
  
  //pinMode(5, OUTPUT);
  bldc.attach(6);
  
  for (int angle = 1500; angle < 1600; angle++) {
    bldc.writeMicroseconds(angle);
    delay(10);
    Serial.println(angle);
  }
  for (int angle = 1600; angle > 1500; angle--) {
    bldc.writeMicroseconds(angle);
    delay(10);
    Serial.println(angle);
  }

  bldc.writeMicroseconds(1500);
  delay(2000);

  for (int angle = 1500; angle > 1100; angle--) {
    bldc.writeMicroseconds(angle);
    delay(10);
    Serial.println(angle);
  }
  for (int angle = 1100; angle < 1500; angle++) {
    bldc.writeMicroseconds(angle);
    delay(10);
    Serial.println(angle);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
