/**
 * @file RCController6CH.h
 * @breif Header file for RCController6CH class
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2018-03-06
 */

#include <IntervalTimer.h>

#ifndef RC_CONTROLLER_6CH_H_
#define RC_CONTROLLER_6CH_H_

#define CH_VALUE_MIN 1200 // min PPM signal in microseconds
#define CH_VALUE_MAX 1800 // max PPM signal in microseconds

#define CH_VALUE_MAP_MIN -100 // minimum value to map the RC controller input to
#define CH_VALUE_MAP_MAX  100 // maximum value to map the RC controller input to

#define CH_MAP_TYPE_BINARY         1 // maps channel values to 0 to 1
#define CH_MAP_TYPE_UNIDIRECTIONAL 2 // maps channel values to 0 to 100
#define CH_MAP_TYPE_BIDIRECTIONAL  3 // maps channel values to -100 to 100

#define MAX_CHANNELS 6 // max channels of the RC controller

#define CHANNEL_UPDATE_RATE 100000 // update rate in microseconds
#define PULSE_IN_TIMEOUT    100000 // timeout for pulse function in microseconds

struct RCController6CHState {
  volatile long int timestamp;  // time of last update
  volatile int value_ch_1;
  volatile int value_ch_2;
  volatile int value_ch_3;
  volatile int value_ch_4;
  volatile int value_ch_5;
  volatile int value_ch_6;
  volatile int *values[6] = {&value_ch_1, &value_ch_2, &value_ch_3, 
      &value_ch_4, &value_ch_5, &value_ch_6}; // iterate through channel values
};
struct RCController6CHPins {
  int PIN_CH_1;
  int PIN_CH_2;
  int PIN_CH_3;
  int PIN_CH_4;
  int PIN_CH_5;
  int PIN_CH_6;
  int *PINS[6] = {&PIN_CH_1, &PIN_CH_2, &PIN_CH_3, &PIN_CH_4, 
      &PIN_CH_5, &PIN_CH_6}; // iterate through pins
};

class RCController6CH {
public:

  /* Constructor Funcitons */
  RCController6CH(int, void (*)());
  /** @fn RCController6CH(int, void (*)())
   *  @brief Default constructor
   *  @author Frederick Wachter
   *  @date Created: 2018-03-08
   */

  RCController6CH(int, int, int, int, int, int, void (*)());
  /** @fn RCController6CH(int, int, int, int, int, int, void (*)())
   *  @brief Specifying all input channel pins
   *  @author Frederick Wachter
   *  @date Created: 2018-03-08
   */

  /* Public Funcitons */
  void setupController(void (*)());
  /** @fn void setupController(void (*)())
   *  @brief Setup controller pins and timed interrupt to update channels
   *  @author Frederick Wachter
   *  @date Created: 2018-03-08
   */

  void updateChannels(void);
  /** @fn void updateChannels(void)
   *  @brief Update the channel values
   *  @author Frederick Wachter
   *  @date Created: 2018-03-08
   */

  void displayChannels(void);
  /** @fn void displayChannels(void)
   *  @brief Display all the current channel values to the serial monitor
   *  @author Frederick Wachter
   *  @date Created: 2018-03-08
   */

  int getChannelVal(int);

protected:

  RCController6CHState state;
  RCController6CHPins  pins;

  int CH_UPDATE_RATE = CHANNEL_UPDATE_RATE; // frequency at which the controller input model is executed

  friend class OmniRobot; // allow omni robot to access protected variables
  friend class OffenseRobot; // allow offense robot to access protected variables

private:

  IntervalTimer _interval_timer;

};

#endif /* RC_CONTROLLER_6CH_H_ */


