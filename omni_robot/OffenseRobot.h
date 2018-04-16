/**
 * @file OffenseRobot.h
 * @breif Header file for OffenseRobot class derived from the OmniRobot class
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2018-04-08
 */

#ifndef OFFENSE_ROBOT_H_
#define OFFENSE_ROBOT_H_

#include <Servo.h>

#include "OmniRobot.h"

#define BLDC_DELAY 10 // time to wait in milliseconds between actuating BLDC's

#define PIN_PWM_SHOOT_LEFT  6
#define PIN_PWM_SHOOT_RIGHT 5
#define PIN_PWM_PUSHER      7

#define PUSHER_INPUT_MIN   -50
#define PUSHER_OUTPUT_MIN 1450
#define PUSHER_OUTPUT_MAX 1700

#define SHOOT_INPUT_CAPTURE_THRESH  75
#define SHOOT_INPUT_OFF_THRESH       0
#define SHOOT_INPUT_SHOOT_THRESH   -75

#define SHOOT_OUTPUT_CAPTURE 1550
#define SHOOT_OUTPUT_OFF     1500
#define SHOOT_OUTPUT_SHOOT   1200

struct ShooterState {
  volatile int position;
  volatile int speed;
};

class OffenseRobot : public OmniRobot {
public:

  /* Constructor Functions */
  OffenseRobot(void);
  /** @fn OffenseRobot(void)
   *  @brief Default constructor
   *  @author Frederick Wachter
   *  @date Created: 2018-04-08
   */

  /* Public Functions */
  int runShooter(Servo&, Servo&);
  /** @fn void runShooter(void)
   *  @brief Actuates the shooter based on input from the RC controller
   *  @author Frederick Wachter
   *  @date Created: 2018-03-15
   */

  void displayShooterState(void);
  /** @fn void displayShooterState(void)
   *  @brief Displays the shooter state
   *  @author Frederick Wachter
   *  @date Created: 2018-03-15
   */

  // void updateLED(void);
  /** @fn void updateLED(void)
   *  @brief Updates LED colors based on robot state
   *  @author Frederick Wachter
   *  @date Created: 2018-03-06
   */

  // Motor shoot_left;
  // Motor shoot_right;

protected:

  ShooterState   shooter_state;
  Motor pusher;

};

#endif /* OFFENSE_ROBOT_H_ */


