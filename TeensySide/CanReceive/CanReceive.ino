#include "FlexCAN.h" // https://github.com/pawelsky/FlexCAN_Library

#define STBY 28

// #define TEMP_MON

FlexCAN bus(500000, 0, 1, 1);
CAN_message_t message;
String msgString;

void setup() {
	Serial.begin(9600);
	bus.begin();

	// standby pin needs to be set low if on TEMP_MON
	#ifdef TEMP_MON
		digitalWrite(STBY, LOW);
	#endif
}

void loop() {
	delay(500);

	// bus.available() returns 1 if there is a message on the bus
	if(bus.available()) {
		bus.read(message);
		printMessage(message);
	}
}

// prints the message treating each element as an ASCII value
void printMessage(CAN_message_t msg) {
	msgString = "";

	for(int i = 0; i < msg.len; i++)
		msgString += msg.buf[i];

	Serial.println(msgString);
}