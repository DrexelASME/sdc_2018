/** 
 * @file rc_comm.ino
 * @brief Example of how to get data from RC controller
 * @author Frederick Wachter - wachterfreddy@gmail.com
 * @date Created: 2017-01-27
 */

#define PULSEIN_TIMEOUT 100000 // 0.1 second timeout

const int CH1 = 27;
const int CH2 = 28;
int CH1_OFFSET, CH2_OFFSET;

void setup() {
  
	Serial.begin(9600);
	pinMode(CH1, INPUT);
	pinMode(CH2, INPUT);

	while (pulseIn(CH1, HIGH, PULSEIN_TIMEOUT) == 0) {
		delay(100);
	}

	CH1_OFFSET = pulseIn(CH1, HIGH, PULSEIN_TIMEOUT);
	CH2_OFFSET = pulseIn(CH2, HIGH, PULSEIN_TIMEOUT);
  
}

void loop() {
  
	int channel_1 = pulseIn(CH1, HIGH, PULSEIN_TIMEOUT);
	int channel_2 = pulseIn(CH2, HIGH, PULSEIN_TIMEOUT);

	Serial.print("CH1: ");
	Serial.print(channel_1);
	Serial.print(" | CH2: ");
	Serial.println(channel_2);

  delay(100);
  
}
