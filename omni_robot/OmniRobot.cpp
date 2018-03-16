/**
 * @file OmniRobot.cpp
 * @breif Implementation file for OmniRobot class
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2018-02-14
 */

#include <Arduino.h>
#include <math.h>

#include "Logger.h"
#include "OmniRobot.h"

/* CONSTRUCTOR FUNCTIONS */
OmniRobot::OmniRobot(void) :
			drive_left( MOTOR_TYPE_DC,    PIN_PWM_LEFT,         PIN_A_LEFT,  PIN_B_LEFT),
			drive_right(MOTOR_TYPE_DC,    PIN_PWM_RIGHT,        PIN_A_RIGHT, PIN_B_RIGHT),
			drive_tail( MOTOR_TYPE_DC,    PIN_PWM_TAIL,         PIN_A_TAIL,  PIN_B_TAIL),
			shoot_left( MOTOR_TYPE_BLDC,  PIN_PWM_SHOOT_LEFT),
			shoot_right(MOTOR_TYPE_BLDC,  PIN_PWM_SHOOT_RIGHT),
			pusher(     MOTOR_TYPE_SERVO, PIN_PWM_PUSHER),
			rc_controller(PIN_CH_1, &updateController) {

}

/* PUBLIC FUNCTIONS */
void OmniRobot::runRobotModel(void) {
	
	// Initialize variables
	int x_input;    // x input in the body frame of the robot
	int y_input;    // y input in the body frame of the robot
	int spin_input; // spin input in the body frame of the robot

	int max_wheel_speed; // max speed of the three wheels
	
	// Get x, y, and spin input from controller
	cli();
	x_input    =  rc_controller.state.value_ch_2;
	y_input    = -rc_controller.state.value_ch_1;
	spin_input = -rc_controller.state.value_ch_4;
	sei();

	// Apply dead zone for controller
	_applyDeadZone(&x_input, &y_input, &spin_input);

	// Calculate speed and direction in the body frame
	state.body_spin      = int(SPIN_GAIN * spin_input);
	state.body_speed     = constrain(sqrt(x_input*x_input + y_input*y_input), SPEED_MIN, SPEED_MAX);
	state.body_direction = atan2(y_input, x_input);

	// Calcualte individual wheel speeds
	state.wheel_speed_left  = int(state.body_speed * cos(-150.0*DEG_TO_RAD + state.body_direction)) + state.body_spin;
	state.wheel_speed_right = int(state.body_speed * cos( -30.0*DEG_TO_RAD + state.body_direction)) + state.body_spin;
	state.wheel_speed_tail  = int(state.body_speed * cos(-270.0*DEG_TO_RAD + state.body_direction)) + state.body_spin;

	// Check if any wheels are maxed out and adjust accordingly to make sure max wheel speed is 100
	max_wheel_speed = max(state.wheel_speed_left, max(state.wheel_speed_right, state.wheel_speed_tail));
	if (max_wheel_speed > SPEED_MAX) {
		double speed_scale = ((SPEED_MAX - state.body_spin) / double(max_wheel_speed - state.body_spin));
		state.wheel_speed_left  = floor((state.wheel_speed_left  - state.body_spin) * speed_scale)  + state.body_spin;
		state.wheel_speed_right = floor((state.wheel_speed_right - state.body_spin) * speed_scale)  + state.body_spin;
		state.wheel_speed_left  = floor((state.wheel_speed_tail  - state.body_spin) * speed_scale)  + state.body_spin;
	}

	// Move motors at desired speeds
	drive_left.run( state.wheel_speed_left);
	drive_right.run(state.wheel_speed_right);
	drive_tail.run( state.wheel_speed_tail);

}

void OmniRobot::runShooter(void) {

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

	shooter_state.speed = map(shoot_input, -100, 100, 1200, 1800);
	// // Map shoot input into relevant values
	// if (shoot_input > SHOOT_INPUT_CAPTURE_THRESH) {
	// 	shooter_state.speed = SHOOT_OUTPUT_CAPTURE;
	// } else if (shoot_input < SHOOT_INPUT_SHOOT_THRESH) {
	// 	shooter_state.speed = SHOOT_OUTPUT_SHOOT;
	// } else {
	// 	shooter_state.speed = SHOOT_OUTPUT_OFF;
	// }

	// Set pusher and shoot motrs to desired location/speed
	pusher.run(     shooter_state.position);
	shoot_left.run( shooter_state.speed);
	delay(10);
	shoot_right.run(shooter_state.speed);

}

void OmniRobot::displayRobotState(void) {

	logger::displayInfo("Robot State: " + String(state.wheel_speed_left) + " (left) | " + 
			String(state.wheel_speed_right) + " (right) | " + String(state.wheel_speed_tail) + 
			" (tail) | " + String(state.body_speed) + " (body speed) | " + String(state.body_direction) 
			+ " (body direction) | " + String(state.body_spin) + " (body spin)");

}

void OmniRobot::displayShooterState(void) {

	logger::displayInfo("Shooter State: " + String(shooter_state.position) + " (position) | " + 
			String(shooter_state.speed) + " (speed)");

}

void OmniRobot::displayRCChannels(void) {

	rc_controller.displayChannels();

}

void OmniRobot::updateRCChannels(void) {

	rc_controller.updateChannels();

}

 void OmniRobot::_applyDeadZone(int *input_1, int *input_2, int *input_3) {

	if (abs(*input_1) < DEAD_ZONE) {
		*input_1 = 0;
	}
	if (abs(*input_2) < DEAD_ZONE) {
		*input_2 = 0;
	}
	if (abs(*input_3) < DEAD_ZONE) {
		*input_3 = 0;
	}

}


