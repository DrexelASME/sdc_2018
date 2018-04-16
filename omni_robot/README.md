# ASME SDC 2018 - Robot Library Class Skeletons

The skeleton code for the classes being made for the 2018 ASME SDC robots is shown below.

## Table of Contents
- [Installations](#install)
- [OmniRobot Class](#omnirobot)
- [Motor Class](#motor)
- [Encoder Class](#encoder)
- [Sensor Class](#sensor)
- [6 Channel RC Controller Class](#rccontroller)
- [LED Class](#led)

## Revisions List
Full Name | Email | Date | Revision | Description
--- | --- | --- | --- | ---
Frederick Wachter | wachterfreddy@gmail.com | 2018-02-25 | 0.0.0 | Initial document
Frederick Wachter | wachterfreddy@gmail.com | 2018-03-08 | 0.0.1 | Install for MAG3110

<a id="install"/>

## Installations

#### Sensor Class Dependencies

The sensor class depends on the Sparkfun MAG3110 library that be found [here](https://goo.gl/6krKLD). This library
will need to be added to the libraries folder of the Arduino IDE. More information on the MAG3110 can be found 
[here](https://goo.gl/mLZ2gx).

[Back to top](#top)

<a id="omnirobot"/>

## OmniRobot Class

This class is used to define the ASME SDC 2018 Omni-Wheeled robot used for the ASME SDC 2018 SDC (Student Design 
Competition).

```cpp
#ifndef OMNI_ROBOT_H_
#define OMNI_ROBOT_H_

#include "LED.h"             // LED status class
#include "Motor.h"           // Motor class
#include "RCController6CH.h" // 6 channel RC controller class
#include "Sensor.h"          // Sensor class

class OmniRobot {
public:
	Motor drive_right();
	Motor drive_left();
	Motor drive_tail();
	Motor shoot_left();
	Motor shoot_right();
	Motor pusher();

	Sensor compass();
	Sensor current(); // current being used by the whole robot
	Sensor ir_ball(); // sensor used to tell if a ball has been captured
	Sensor ir_capture(); // sensor used to tell if a ball is infront of the robot or not

	RCController6CH rc_controller();

	void encoderModel() {
		// Code goes here ...
	}
	void controllerInputModel() { // maybe not needed? maybe define in rc controller class?
		// Code goes here ...
	}
	void robotModel() {
		// Code goes here ...
	}
};

#endif /* OMNI_ROBOT_H_ */
```

[Back to top](#top)


<a id="motor"/>

## Motor Class

This class is used for motors that have an encoder that works with the Encoder class and has an optional current 
sensor.

```cpp
#ifndef MOTOR_H_
#define MOTOR_H_

#include "Encoder.h" // Encoder class and MOTOR_DIR_CW MOTOR_DIR_CCW
#include "Sensor.h"  // Sensor class

#define MOTOR_TYPE_DC    1
#define MOTOR_TYPE_BLDC  2
#define MOTOR_TYPE_SERVO 3

struct MotorState {
	int duty_cycle; // value between 0 and 100
	bool direction; // either MOTOR_DIR_CW or MOTOR_DIR_CCW (from Encoder.h)
};
struct MotorPins {
	int PIN_PWM;
	int PIN_A;
	int PIN_B;
};

class Motor {
public:
	void setupMotor();
	double getCurrentUsage();
	double getMotorPosition();

protected:
	MotorState state;
	MotorPins  pins;
	static int TOTAL_MOTORS;

private:
	Encoder encoder;
	Sensor current;
};

#endif /* MOTOR_H_ */
```

[Back to top](#top)


<a id="encoder"/>

## Encoder Class

This is a generalized class for an encoder.

```cpp
#ifndef ENCODER_H_
#define ENCODER_H_

#define ENCODER_TYPE_INCREMENTAL 1
#define ENCODER_TYPE_QUADRATURE  2
#define ENCODER_TYPE_ABSOLUTE    3

#define MOTOR_DIR_CW  0 
#define MOTOR_DIR_CCW 1

struct EncoderState {
	volatile long int timestamp; // time of last update
	volatile long int position;
	volatile bool direction;
};
struct EnoderPins {
	int PIN_A;
	int PIN_B;
};

class Encoder {
public:
	void setupEncoder();

protected:
	EncoderState state;
	EncoderPins  pins;

private:
	void encoderInterrupt();
};

#endif /* ENCODER_H_ */
```

[Back to top](#top)


<a id="sensor"/>

## Sensor Class

This is a generalized sensor class for the current, IR TOF (time-of-flight), and compass sensors.

```cpp
#ifndef SENSOR_H_
#define SENSOR_H_

#define SENSOR_TYPE_CURRENT    1
#define SENSOR_TYPE_IR_DIGITAL 2
#define SENSOR_TYPE_COMPASS    3

#define SENSOR_COMM_TYPE_DIGITAL 1
#define SENSOR_COMM_TYPE_PULSE   2 // PWM or PPM
#define SENSOR_COMM_TYPE_I2C     3

struct SensorState {
	volatile long int timestamp; // time of last update
	volatile double data;
};
struct SensorPins {
	int PIN_DATA;
	int PIN_CLOCK;
	int PIN_INTERRUPT;
};

class Sensor {
public:
	void setupDataInterrupt();

protected:
	SensorState state;
	SensorPins  pins;
	static int TOTAL_SENSORS;

	int COMM_TYPE;
	int DATA_SCALAR;
	bool INTERRUPTABLE; // whether data can be updated on interrupt or not
};

#endif /* SENSOR_H_ */
```

[Back to top](#top)


<a id="rccontroller"/>

## 6 Channel RC Controller Class

This class is used to take the stick inputs from an RC controller through a 6CH receiver.

```cpp
#ifndef RC_CONTROLLER_6CH_H_
#define RC_CONTROLLER_6CH_H_

#define DEFAULT_CH_VALUE_MIN 1000 // min PPM signal in microseconds
#define DEFAULT_CH_VALUE_MAX 2000 // max PPM signal in microseconds

#define CH_MAP_TYPE_BINARY         1 // maps channel values to 0 to 1
#define CH_MAP_TYPE_UNIDIRECTIONAL 2 // maps channel values to 0 to 100
#define CH_MAP_TYPE_BIDIRECTIONAL  3 // maps channel values to -100 to 100

struct RCController6CHState {
	volatile long int timestamp;  // time of last update
	volatile int value_ch_1;
	volatile int value_ch_2;
	volatile int value_ch_3;
	volatile int value_ch_4;
	volatile int value_ch_5;
	volatile int value_ch_6;
	int *values[] = {&value_ch_1, &value_ch_2, &value_ch_3, &value_ch_4, 
			&value_ch_5, &value_ch_6}; // iterate through channel values
};
struct RCController6CHPins {
	int PIN_CH_1;
	int PIN_CH_2;
	int PIN_CH_3;
	int PIN_CH_4;
	int PIN_CH_5;
	int PIN_CH_6;
	int *PINS[] = {&PIN_CH_1, &PIN_CH_2, &PIN_CH_3, &PIN_CH_4, &PIN_CH_5, &PIN_CH_6}; // iterate through pins
};

class RCController6CH {
public:
	void setupChannel(int channel, int map_type, int threshold);
	void setupChannel(int channel, int map_type, int min_value, int max_value);

protected:
	RCController6CHState state;
	RCController6CHPins  pins;
	int CH_UPDATE_HZ; // frequency at which the controller input model is executed

private:
	void runControllerInputModel(); // defined in robot class
	void setupControllerInputTimerInterupt(); // interrupt to update controller input model
	void setupChannelInterrupts();
};

#endif /* RC_CONTROLLER_6CH_H_ */
```

[Back to top](#top)


<a id="led"/>

## LED Class

This class is used to determine the various states and error that the robot class can run into and what color sequence
to show on the LED strip during these events in order to indicate this information to the user.

**NOTE:** **_Still needs to be defined_**

```cpp
#ifndef LED_H_
#define LED_H_

class LED {

};

#endif /* LED_H_ */
```

[Back to top](#top)


