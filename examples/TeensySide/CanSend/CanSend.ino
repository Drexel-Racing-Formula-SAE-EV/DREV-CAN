#include "FlexCAN.h" // https://github.com/pawelsky/FlexCAN_Library

// #define TEMP_MON
#define STBY 28
#define ID 0x631

FlexCAN bus(500000, 0, 1, 1); // The last two parameters specify the use of pins 29 & 30 instead of 3 & 4
CAN_message_t message;
unsigned long lastWrite = 0;
int counter = 0;

void setup() {
 	Serial.begin(9600);
	bus.begin();

	// standby pin needs to be set low if on TEMP_MON
	#ifdef TEMP_MON
		digitalWrite(STBY, LOW);
	#endif

    message.len = 8;
    message.id = 0;
}

void loop() {
	if(millis() - lastWrite > 1000) {
		message.buf[0] = counter++;
		
        if(bus.write(message)) {
			Serial.print("sent message: ");
			Serial.println(counter);
		} else
			Serial.println("message failed to send");
        
        lastWrite = millis();
	}
}

// void writeBuffer(int )

// most likely not going to use this function
void writeBuffer(String text) {
	for(int i = 0; i < message.len; i++)
		message.buf[i] = text.charAt(i);
}