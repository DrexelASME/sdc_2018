/**
* @file Logger.cpp
* @breif Implementation file for error codes
* @author Frederick Wachter - wachterfreddy@gmail.com
* @date Created: 2018-03-07
*/

#include "Logger.h"

int logger::displayError(int error_code) {

  Serial.print("[ERROR] ");

  switch (error_code) {
    case MOTOR_TYPE_ERROR:
      Serial.println("Provided motor type not recognized");
      return MOTOR_TYPE_ERROR;
    case ENCODER_SETUP_ERROR:
      Serial.println("Requesting information from encoder when it has not been setup yet");
      return ENCODER_SETUP_ERROR;
    case SENSOR_TYPE_ERROR:
      Serial.println("Provided sensor type not recognized");
      return SENSOR_TYPE_ERROR;
    case SENSOR_INT_ERROR:
      Serial.println("Sensor is interruptable but no interrupt function was provided");
      return SENSOR_INT_ERROR;
    case LED_STATE_ERROR:
      Serial.println("Provided LED state is not valid");
      return LED_STATE_ERROR;
  }

  return error_code;

}

void logger::displayInfo(String message) {

  Serial.print("[INFO] ");
  Serial.println(message);

}

void logger::displayDebug(String message) {

  if (DEBUG_LOGGER_LEVEL) {
    Serial.print("[DEBUG] ");
    Serial.println(message);
  }

}


