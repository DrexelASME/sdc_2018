/**
 * @file OffenseRobot.cpp
 * @breif Implementation file for OffenseRobot class derived from the OmniRobot class
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2018-04-08
 */

#include <Arduino.h>

#include "Logger.h"
#include "OffenseRobot.h"

/* CONSTRUCTOR FUNCTIONS */
OffenseRobot::OffenseRobot(void) :
      // shoot_left( MOTOR_TYPE_BLDC,  PIN_PWM_SHOOT_LEFT),
      // shoot_right(MOTOR_TYPE_BLDC,  PIN_PWM_SHOOT_RIGHT),
      pusher(     MOTOR_TYPE_SERVO, PIN_PWM_PUSHER) {

}

/* PUBLIC FUNCTIONS */
int OffenseRobot::runShooter(Servo &shoot_left, Servo &shoot_right) {

  // Initialized Variables
  int pusher_input; // input for actuating the linear actuator
  int shoot_input;  // input for actuating the shoot motors

  // Get pusher and shoot input from controller
  cli();
  pusher_input = rc_controller.state.value_ch_3;
  shoot_input  = rc_controller.state.value_ch_5;
  sei();

  // Map pusher input into relevant values
  pusher_input = map(pusher_input, PUSHER_INPUT_MIN, CH_VALUE_MAP_MAX, PUSHER_OUTPUT_MIN, PUSHER_OUTPUT_MAX);
  pusher_input = constrain(pusher_input, PUSHER_OUTPUT_MIN, PUSHER_OUTPUT_MAX);
  shooter_state.position = (pusher_input/10)*10; // set the last digit to zero to avoid moving actuator too much

  // shooter_state.speed = map(shoot_input, -100, 100, 1200, 1800);
  // Map shoot input into relevant values
  if (shoot_input > SHOOT_INPUT_CAPTURE_THRESH) {
    shooter_state.speed = SHOOT_OUTPUT_CAPTURE;
  } else if (shoot_input < SHOOT_INPUT_SHOOT_THRESH) {
    shooter_state.speed = SHOOT_OUTPUT_SHOOT;
  } else {
    shooter_state.speed = SHOOT_OUTPUT_OFF;
  }

  // Set pusher and shoot motrs to desired location/speed
  pusher.run(shooter_state.position);

  return shooter_state.speed;

}

void OffenseRobot::displayShooterState(void) {

  logger::displayInfo("Shooter State: " + String(shooter_state.position) + " (position) | " + 
      String(shooter_state.speed) + " (speed)");

}

// void OffenseRobot::updateLED(void) {

//   if (shoot_left.ready == false) {
//     Serial.println("Shoot left: " + String(shoot_left.ready));
//     led.setState(COLOR_YELLOW, BLINK_ON, SIDE_LEFT);
//     return;
//   }
//   if (shoot_right.ready == false) {
//     Serial.println("Shoot right: " + String(shoot_right.ready));
//     led.setState(COLOR_YELLOW, BLINK_ON, SIDE_RIGHT);
//     return;
//   }

//   OmniRobot::updateLED();

// }


