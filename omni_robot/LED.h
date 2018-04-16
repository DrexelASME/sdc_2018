/**
 * @file LED.h
 * @breif Header file for LED class
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2018-03-06
 */

#ifndef LED_H_
#define LED_H_

// #define COMMON_ANODE // comment if not using a common anode LED

#define COLOR_NONE    0
#define COLOR_RED     1
#define COLOR_YELLOW  2
#define COLOR_GREEN   3
#define MIN_STATE_VAL 0
#define MAX_STATE_VAL 3

#define MIN_COLOR_VALUE 0
#define MAX_COLOR_VALUE 255

#define BLINK_OFF     0
#define BLINK_ON      1
#define BLINK_SPEED 250 // speed at which to blink in miliseconds
 
#define SIDE_BOTH     0
#define SIDE_LEFT     1
#define SIDE_RIGHT    2

struct LEDState {
  int led;
  int red;
  int green;
  int blue;
  int side;
  bool is_blink;
  bool blink;
  uint32_t blink_start;
};

struct LEDPins {
  int PIN_LEFT_RED;
  int PIN_LEFT_GREEN;
  int PIN_LEFT_BLUE;
  int PIN_RIGHT_RED;
  int PIN_RIGHT_GREEN;
  int PIN_RIGHT_BLUE;
};

class LED {
public:
  LED(int, int, int, int, int, int);

  void setup(int, int, int, int, int, int);
  void setState(int, bool blink = false, int side = SIDE_BOTH);
  void getState(void);

protected:
  LEDState state;
  LEDPins  pins;

private:
  void _updateState(void);
  void _updateBlink(void);
  void _setColor(int, int, int, int);

};

#endif /* LED_H_ */


