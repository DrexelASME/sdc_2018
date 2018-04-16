/**
 * @file OmniRobot.h
 * @breif Header file for OmniRobot class
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2018-02-14
 */

#ifndef OMNI_ROBOT_H_
#define OMNI_ROBOT_H_

#include "LED.h"             // LED status class
#include "Motor.h"           // Motor class
#include "RCController6CH.h" // 6 channel RC controller class
// #include "Sensor.h"          // Sensor class

#define PIN_PWM_LEFT        2
#define PIN_PWM_RIGHT       3
#define PIN_PWM_TAIL        4

#define PIN_A_TAIL  33
#define PIN_B_TAIL  34
#define PIN_A_RIGHT 35
#define PIN_B_RIGHT 36
#define PIN_A_LEFT  37
#define PIN_B_LEFT  38

#define PIN_CH_1 27

#define PIN_LEFT_RED     9
#define PIN_LEFT_GREEN  10
#define PIN_LEFT_BLUE    8
#define PIN_RIGHT_RED   22
#define PIN_RIGHT_GREEN 21
#define PIN_RIGHT_BLUE  23

#define SPEED_MIN   0
#define SPEED_MAX 100
#define DEAD_ZONE  10
#define SPIN_GAIN   0.3

void updateController(void);

struct OmniRobotState {
  volatile int body_spin;
  volatile double body_speed;
  volatile double body_direction;

  volatile int wheel_speed_left;
  volatile int wheel_speed_right;
  volatile int wheel_speed_tail;
};

class OmniRobot {
public:

  bool ready = false;

  /* Constructor Functions */
  OmniRobot(void);
  /** @fn OmniRobot(void)
   *  @brief Default constructor
   *  @author Frederick Wachter
   *  @date Created: 2018-03-06
   */

  /* Public Functions */
  void runRobotModel(void);
  /** @fn void runRobotModel(void)
   *  @brief Executes the robot model based on input from the RC controller
   *  @author Frederick Wachter
   *  @date Created: 2018-03-06
   */

  void displayRobotState(void);
  /** @fn void displayRobotState(void)
   *  @brief Displays the robot state
   *  @author Frederick Wachter
   *  @date Created: 2018-03-06
   */

  void displayRCChannels(void);
  /** @fn void displayRCChannels(void)
   *  @brief Displays all the values from the RC controller
   *  @author Frederick Wachter
   *  @date Created: 2018-03-06
   */

  void updateRCChannels(void);
  /** @fn void updateRCChannels(void)
   *  @brief Updates the RC controller values
   *  @author Frederick Wachter
   *  @date Created: 2018-03-06
   */

  void updateLED(void);
  /** @fn void updateLED(void)
   *  @brief Updates LED colors based on robot state
   *  @author Frederick Wachter
   *  @date Created: 2018-03-06
   */

  RCController6CH rc_controller;

protected:

  OmniRobotState state;

  LED led;

  Motor drive_left;
  Motor drive_right;
  Motor drive_tail;

  // Sensor compass();
  // Sensor current(); // current being used by the whole robot
  // Sensor ir_ball(); // sensor used to tell if a ball has been captured
  // Sensor ir_capture(); // sensor used to tell if a ball is infront of the robot or not

private:

  static void _applyDeadZone(int*, int*, int*);
  /** @fn static void _applyDeadZone(int*, int*, int*)
   *  @brief Applies a dead zone to the controller input
   *  @author Frederick Wachter
   *  @date Created: 2018-03-15
   */

};

#endif /* OMNI_ROBOT_H_ */


