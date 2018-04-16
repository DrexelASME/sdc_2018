/**
* @file Motor.cpp
* @breif Implementation file for Motor class
* @author Frederick Wachter - wachterfreddy@gmail.com
* @date Created: 2018-03-06
*/

#include "Logger.h"
#include "Motor.h"

/* CONSTRUCTOR FUNCTIONS */
Motor::Motor(int type, int pin_pwm, int pin_a, int pin_b) :
      _encoder(NO_ENCODER_PIN, NO_ENCODER_PIN) {

  setupMotor(type, pin_pwm, pin_a, pin_b);

}

Motor::Motor(int type, int pin_pwm, int pin_a, int pin_b, 
    int encoder_pin_a, int encoder_pin_b) :
      _encoder(encoder_pin_a, encoder_pin_b) {

  _encoder.write(0);
  ENCODER_SETUP = true;

  setupMotor(type, pin_pwm, pin_a, pin_b);

}

/* PUBLIC FUNCTIONS */
int Motor::setupMotor(int type, int pin_pwm, int pin_a, int pin_b) {
/** @return error code
*/

  // Initialize motor state
  state.speed     = 0; // set initial speed to zero
  state.direction = MOTOR_FORWARD; // set initial direction to forward

  // Store motor pins
  pins.PIN_PWM = pin_pwm;

  // Setup motor pins
  pinMode(pins.PIN_PWM, OUTPUT);

  // Check motor type
  if ((type < MOTOR_TYPE_MIN) || (type > MOTOR_TYPE_MAX)) {
    return logger::displayError(MOTOR_TYPE_ERROR);
  } else {
    state.type = type;
  }

  // Setup motor
  if (state.type == MOTOR_TYPE_DC) {
    _setupDCMotor(pin_a, pin_b);
  } if (state.type == MOTOR_TYPE_BLDC) {
    _setupBLDCMotor();
  }

  ready = true;
  logger::displayInfo(_getMotorTypeName() + " motor has been setup");
  return SUCCESS;

}

void Motor::run(int speed) {
/** @return error code
*/

  if (speed > 0) {
    state.direction = MOTOR_FORWARD;
  } else if (speed < 0) {
    state.direction = MOTOR_REVERSE;
  } else {
    state.direction = MOTOR_BRAKE;
  }

  if (state.type == MOTOR_TYPE_DC) {
    return _runDCMotor(speed);
  } else if (state.type == MOTOR_TYPE_BLDC) {
    return _runBLDCMotor(speed);
  } else if (state.type == MOTOR_TYPE_SERVO) {
    return _runServoMotor(speed);
  }

}

long Motor::getPosition(void) {
/** @return motor_position - position of the motor
*/

  if (!ENCODER_SETUP) {
    return logger::displayError(ENCODER_SETUP_ERROR);
  }

  long int motor_position = _encoder.read(); // get encoder position

  return motor_position;

}

/* PUBLIC FUNCTIONS */
void Motor::_setupDCMotor(int pin_a, int pin_b) {

// Store motor pins
  pins.PIN_A = pin_a;
  pins.PIN_B = pin_b;

// Setup motor pins
  pinMode(pins.PIN_A, OUTPUT);
  pinMode(pins.PIN_B, OUTPUT);

}

void Motor::_setupBLDCMotor(void) {

  // Setup BLDC
  // _servo.attach(pins.PIN_PWM, MOTOR_PPM_MIN, MOTOR_PPM_MAX);
  // delay(1);
  // _servo.write(40);

  // for (int angle = 1500; angle < 1600; angle++) {
  //   _servo.writeMicroseconds(angle);
  //   delay(10);
  //   Serial.println(angle);
  // }
  // for (int angle = 1600; angle > 1500; angle--) {
  //   _servo.writeMicroseconds(angle);
  //   delay(10);
  //   Serial.println(angle);
  // }

  // Arm ESC's
  // cli();
  // for(int i = 0; i < 130; i++)
  // {
  //    _servo.write(i);
  //    Serial.println(i);
  //    delay(50);
  // }
  // for(int i = 130; i > -1; i--)
  // {
  //    _servo.write(i);
  //    Serial.println(i);
  //    delay(50);
  // }

  // for (int ppm = 45; ppm < 60; ppm++) {
  //   _servo.write(ppm);
  //   delay(ESC_ARM_DELAY);
  // }
  // for (int ppm = 60; ppm > 30; ppm--) {
  //   _servo.write(ppm);
  //   delay(ESC_ARM_DELAY);
  // }
  // for (int ppm = 45; ppm < 90; ppm++) {
  //   _servo.write(ppm);
  //   delay(ESC_ARM_DELAY);
  // }
  // for (int ppm = 90; ppm > 0; ppm--) {
  //   _servo.write(ppm);
  //   delay(ESC_ARM_DELAY);
  // }  
  // for (int ppm = 0; ppm < 45; ppm++) {
  //   _servo.write(ppm);
  //   delay(ESC_ARM_DELAY);
  // }

  // long int mil = millis();
  // while ((millis() - mil) < 2000) {
  //   analogWriteFrequency(pins.PIN_PWM, 50);
  //   analogWrite(pins.PIN_PWM, 127);
  // }
  // mil = millis();
  // while ((millis() - mil) < 2000) {
  //   _servo.writeMicroseconds(2000);
  //   Serial.println((millis() - mil));
  //   delay(10);
  // }
  // mil = millis();
  // while ((millis() - mil) < 2000) {
  //   _servo.writeMicroseconds(1000);
  //   Serial.println((millis() - mil));
  //   delay(10);
  // }
  // sei();

  state.speed = MOTOR_PPM_OFF; // set initial speed to zero

}

void Motor::_runDCMotor(int speed) {

  state.speed = abs(speed);

  if (state.direction == MOTOR_FORWARD) {
    digitalWrite(pins.PIN_A, HIGH);
    digitalWrite(pins.PIN_B, LOW);
  } else if (state.direction == MOTOR_BRAKE) {
    digitalWrite(pins.PIN_A, HIGH);
    digitalWrite(pins.PIN_B, HIGH);
  } else if (state.direction == MOTOR_REVERSE) {
    digitalWrite(pins.PIN_A, LOW);
    digitalWrite(pins.PIN_B, HIGH);
  }

  speed = map(state.speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX, MOTOR_PWM_MIN, MOTOR_PWM_MAX);
  speed = constrain(speed, MOTOR_PWM_MIN, MOTOR_PWM_MAX);
  analogWrite(pins.PIN_PWM, speed);

  logger::displayDebug("Running DC motor at speed: " + String(state.speed));

}

void Motor::_runBLDCMotor(int speed) {

  _servo.writeMicroseconds(speed);

}

void Motor::_runServoMotor(int position) {

  // Constrain position and store position
  position = max(min(position, MOTOR_PPM_MAX), MOTOR_PPM_MIN);
  state.speed = position;

  // Set position of the motor
  cli();
  digitalWrite(pins.PIN_PWM, HIGH);
  delayMicroseconds(state.speed);
  digitalWrite(pins.PIN_PWM, LOW);
  sei();

}

String Motor::_getMotorTypeName(void) {
/** @return string of the motor type name
*/

  switch (state.type) {
    case MOTOR_TYPE_DC:
    return "DC";
    case MOTOR_TYPE_BLDC:
    return "Brushless DC";
    case MOTOR_TYPE_SERVO:
    return "Servo";
  }

  return "";

}


