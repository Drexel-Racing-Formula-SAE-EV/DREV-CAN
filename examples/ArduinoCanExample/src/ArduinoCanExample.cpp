#include "Arduino.h"
#include <SPI.h>

#include <drev_can.h>

#define ID 0x631

#define SEND 1
#define RECEIVE 2

#define MODE SEND

drev_can::can_node canBus(ID);
unsigned long last_write_time = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    #if MODE == SEND
        if(millis() - last_write_time > 1000) {
           
           drev_can::can_message message{
            .data[0] = 40 // write test data to a message
           };
            
            // if(mcp2515_send_message(&message))
            //     Serial.println("wrote to bus");
            // else
            //     Serial.println("failed to write to bus");

            Serial.println(canBus.send(message));

            last_write_time = millis();
        }
    #elif MODE == RECEIVE
		Serial.println(canBus.available());
        if(canBus.available()) {
            Serial.println("message available");

			int ret;
            drev_can::can_message message; 

			ret = canBus.readall(message); 
            if(ret == DREV_CAN_NOMSG) {
                Serial.println("no msg");
			} else {
				Serial.print("ID: ");
				Serial.print(canBus.id());
				Serial.print(", Length: ");
				Serial.print(message.length);
				Serial.print(", Data: ");
				for(int i = 0; i < message.length; i++) {
					Serial.print(message.data[i], HEX);
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

