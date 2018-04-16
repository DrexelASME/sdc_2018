/*
Adafruit Arduino - Lesson 3. RGB LED
*/

int pin_blue  = 21;
int pin_red   = 22;
int pin_green = 23;

//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

void setup()
{
  pinMode(pin_red,   OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_blue,  OUTPUT);  
}

void loop()
{
  setColor(255, 0, 0);  // red
  delay(3000);
  setColor(0, 255, 0);  // green
  delay(3000);
  setColor(0, 0, 255);  // blue
  delay(3000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(2000);
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red   = 255 - red;
    green = 255 - green;
    blue  = 255 - blue;
  #endif
  analogWrite(pin_red,   red);
  analogWrite(pin_green, green);
  analogWrite(pin_blue,  blue);  
}
