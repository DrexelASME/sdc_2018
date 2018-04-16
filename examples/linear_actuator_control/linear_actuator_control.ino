/** 
 * @file linear_actuator_control.ino
 * @brief Example of how to actuate a servo linear actuator
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2017-02-14
 */
 
#include <Servo.h>

#define LIN_ACT_MIN 1400
#define LIN_ACT_MAX 1700

Servo linear_actuator;

void setup() {
  linear_actuator.attach(5);
}

void loop() {
  for (int ppm = 1200; ppm < 1800; ppm++) {
  	linear_actuator.writeMicroseconds(ppm);
  	delay(10);
  	Serial.println(ppm);
  }
  for (int ppm = 1800; ppm > 1200; ppm--) {
  	linear_actuator.writeMicroseconds(ppm);
  	delay(10);
  	Serial.println(ppm);
  }
}
