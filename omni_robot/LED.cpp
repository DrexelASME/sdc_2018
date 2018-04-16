/**
* @file LED.cpp
* @breif Implementation file for LED class
* @author Frederick Wachter - wachterfreddy@gmail.com
* @date Created: 2018-03-06
*/

#include <Arduino.h>

#include "LED.h"
#include "Logger.h"

LED::LED(int pin_left_red, int pin_left_green, int pin_left_blue, 
    int pin_right_red, int pin_right_green, int pin_right_blue) {

  setup(pin_left_red, pin_left_green, pin_left_blue, 
    pin_right_red, pin_right_green, pin_right_blue);

}

void LED::setup(int pin_left_red, int pin_left_green, int pin_left_blue, 
    int pin_right_red, int pin_right_green, int pin_right_blue) {

  int min_val = MIN_COLOR_VALUE;

  pins.PIN_LEFT_RED    = pin_left_red;
  pins.PIN_LEFT_GREEN  = pin_left_green;
  pins.PIN_LEFT_BLUE   = pin_left_blue;
  pins.PIN_RIGHT_RED   = pin_right_red;
  pins.PIN_RIGHT_GREEN = pin_right_green;
  pins.PIN_RIGHT_BLUE  = pin_right_blue;

  pinMode(pins.PIN_LEFT_RED,    OUTPUT);
  pinMode(pins.PIN_LEFT_GREEN,  OUTPUT);
  pinMode(pins.PIN_LEFT_BLUE,   OUTPUT);
  pinMode(pins.PIN_RIGHT_RED,   OUTPUT);
  pinMode(pins.PIN_RIGHT_GREEN, OUTPUT);
  pinMode(pins.PIN_RIGHT_BLUE,  OUTPUT);

#ifdef COMMON_ANODE
  min_val = MAX_COLOR_VALUE;
#endif

  _setColor(min_val, min_val, min_val, SIDE_BOTH);
  state.led = -1;

}

void LED::setState(int des_state, bool blink, int side) {

  if ((des_state < MIN_STATE_VAL) || (des_state > MAX_STATE_VAL)) {
    logger::displayError(LED_STATE_ERROR);
    return;
  }
  state.is_blink = blink;
  state.side     = side;

  if (state.led == des_state) {
    if (blink) {
      _updateBlink();
    }
  } else {
    state.led = des_state;
    _updateState();
  }

}

void LED::_updateState(void) {

  int red_value   = COLOR_NONE;
  int green_value = COLOR_NONE;
  int blue_value  = COLOR_NONE;

  int des_state = state.led;

  if ((state.is_blink == true) && (state.blink == BLINK_OFF)) {
    des_state = COLOR_NONE;
  }

  switch (des_state) {
    case COLOR_NONE:
      red_value   = MIN_COLOR_VALUE;
      green_value = MIN_COLOR_VALUE;
      blue_value  = MIN_COLOR_VALUE;
      logger::displayDebug("LED color set to: Off");
      break;
    case COLOR_RED:
      red_value   = MAX_COLOR_VALUE;
      green_value = MIN_COLOR_VALUE;
      blue_value  = MIN_COLOR_VALUE;
      logger::displayDebug("LED color set to: Red");
      break;
    case COLOR_YELLOW:
      red_value   = MAX_COLOR_VALUE;
      green_value = int(MAX_COLOR_VALUE/6.0);
      blue_value  = MIN_COLOR_VALUE;
      logger::displayDebug("LED color set to: Yellow");
      break;
    case COLOR_GREEN:
      red_value   = MIN_COLOR_VALUE;
      green_value = MAX_COLOR_VALUE;
      blue_value  = MIN_COLOR_VALUE;
      logger::displayDebug("LED color set to: Green");
      break;
  }

#ifdef COMMON_ANODE
  red_value   = MAX_COLOR_VALUE - red_value;
  green_value = MAX_COLOR_VALUE - green_value;
  blue_value  = MAX_COLOR_VALUE - blue_value;
#endif

  _setColor(red_value, green_value, blue_value, state.side);

  state.red   = red_value;
  state.green = green_value;
  state.blue  = blue_value;

  state.blink_start = millis();

}

void LED::_updateBlink(void) {

  if ((millis() - state.blink_start) > BLINK_SPEED) {
    state.blink = !state.blink;
    _updateState();
  }

}

void LED::_setColor(int red_value, int green_value, int blue_value, int side) {

  int min_val = MIN_COLOR_VALUE;

#ifdef COMMON_ANODE
  min_val = MAX_COLOR_VALUE;
#endif

  cli();
  if (side == SIDE_BOTH) {
    // analogWrite(pins.PIN_LEFT_RED,    green_value);
    // analogWrite(pins.PIN_LEFT_GREEN,  green_value);
    analogWrite(pins.PIN_LEFT_BLUE,   green_value);
    // analogWrite(pins.PIN_RIGHT_RED,   green_value);
    // analogWrite(pins.PIN_RIGHT_GREEN, green_value);
    analogWrite(pins.PIN_RIGHT_BLUE,  green_value);
    logger::displayDebug("LED displayed on both sides");
    Serial.println(red_value);
  } else if (side == SIDE_LEFT) {
    // analogWrite(pins.PIN_LEFT_RED,    red_value);
    // analogWrite(pins.PIN_LEFT_GREEN,  green_value);
    // analogWrite(pins.PIN_LEFT_BLUE,   blue_value);
    // analogWrite(pins.PIN_RIGHT_RED,   min_val);
    // analogWrite(pins.PIN_RIGHT_GREEN, min_val);
    // analogWrite(pins.PIN_RIGHT_BLUE,  min_val);
    // logger::displayDebug("LED displayed on left side");
  } else if (side == SIDE_RIGHT) {
    // analogWrite(pins.PIN_LEFT_RED,    min_val);
    // analogWrite(pins.PIN_LEFT_GREEN,  min_val);
    // analogWrite(pins.PIN_LEFT_BLUE,   min_val);
    // analogWrite(pins.PIN_RIGHT_RED,   red_value);
    // analogWrite(pins.PIN_RIGHT_GREEN, green_value);
    // analogWrite(pins.PIN_RIGHT_BLUE,  blue_value);
    // logger::displayDebug("LED displayed on right side");
  }
  sei();

}


