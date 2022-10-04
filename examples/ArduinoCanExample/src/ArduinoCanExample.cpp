#include "Arduino.h"
#include <SPI.h>

#include <drev_can.h>

#define ID 0x631

#define SEND 1
#define RECEIVE 2

#define MODE SEND

DrevCan canBus(ID);
unsigned long last_write_time = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    #if MODE == SEND
        if(millis() - last_write_time > 1000) {
            unsigned char message[8];

            // writeBuffer("test", message);
            message[0] = 40;
            
            // if(mcp2515_send_message(&message))
            //     Serial.println("wrote to bus");
            // else
            //     Serial.println("failed to write to bus");

            Serial.println(canBus.sendMessage(message, 1));

            last_write_time = millis();
        }
    #elif MODE == RECEIVE
		Serial.println(canBus.available());
        if(canBus.available()) {
            Serial.println("message available");

			int ret;
            size_t length;
            unsigned char message[8];

			ret = canBus.readMessage(message, &length);
            if(ret == DREV_CAN_NOMSG) {
                Serial.println("no msg");
			} else if(ret == DREV_CAN_WRONGID) {
                Serial.println("wrong id");
			} else {
				Serial.print("ID: ");
				Serial.print(canBus.getId());
				Serial.print(", Length: ");
				Serial.print(length);
				Serial.print(", Data: ");
				for(int i = 0; i < length; i++) {
					Serial.print(message[i], HEX);
					Serial.print(" ");
				}
				
				Serial.println("");
			}
        } else {
            Serial.println("no message (check)");
		}

        delay(500);
    #endif
}

