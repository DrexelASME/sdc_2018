/**
 * @file Logger.h
 * @breif Header file for error codes
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2018-03-06
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <Arduino.h>

#define DEBUG_LOGGER_LEVEL 0 // 0 don't display debug messages, 1 to display them

#define SUCCESS              0
#define MOTOR_TYPE_ERROR    -1 // motor type not recognized
#define ENCODER_SETUP_ERROR -2 // encoder has not been setup yet
#define SENSOR_TYPE_ERROR   -3 // sensor type not recognized
#define SENSOR_INT_ERROR    -4 // interrupt function not provided to interruptable sensor
#define LED_STATE_ERROR     -5 // provided LED state is not valid

namespace logger {

  int displayError(int);
  /** int displayError(int)
   *  @brief Display error message to serial monitor
   *  @author Frederick Wachter
   *  @date Created: 2018-03-07
   */

  void displayInfo(String);
  /** int void displayInfo(String)
   *  @brief Display info message to serial monitor
   *  @author Frederick Wachter
   *  @date Created: 2018-03-07
   */	

  void displayDebug(String);
  /** void displayDebug(String)
   *  @brief Display debug message to serial monitor
   *  @author Frederick Wachter
   *  @date Created: 2018-03-08
   */

};

#endif /* LOGGER_H_ */


