#include "Arduino.h"
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

#define ID 0x631

#define SEND 1
#define RECEIVE 2

#define MODE RECEIVE

unsigned long last_write_time = 0;

int data = 0;

void setup() {
    Serial.begin(9600);

    if(Canbus.init(CANSPEED_500))
        Serial.println("can init successful, speed 500KB");
    else
        Serial.println("can init failed");
}

void loop() {
    #if MODE == SEND
        if(millis() - last_write_time > 1000) {
            tCAN message;
            message.id = ID;
            message.header.rtr = 0;
            message.header.length = 1;

            // writeBuffer("test", message);
            message.data[0] = data;
			data++;

            mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
            
            // if(mcp2515_send_message(&message))
            //     Serial.println("wrote to bus");
            // else
            //     Serial.println("failed to write to bus");

            Serial.println(mcp2515_send_message(&message));

            last_write_time = millis();
        }
    #elif MODE == RECEIVE
        if(mcp2515_check_message()) {
            Serial.println("message available");
            tCAN message;
            if(mcp2515_get_message(&message)) {
                Serial.print("ID: ");
                Serial.print(message.id,HEX);
                Serial.print(", ");
                Serial.print("Data: ");
                Serial.print(message.header.length);
				
                for(int i=0;i<message.header.length;i++) {
                    // Serial.print(message.data[i],HEX);
                    Serial.print(message.data[i]);
                    Serial.print(" ");
                }
                
                Serial.println("");
            } else
                Serial.println("no message (read)");
        } else
            Serial.println("no message (check)");
        delay(500);
    #endif
    
}

void writeBuffer(String text, tCAN message) {
	for(int i = 0; i < message.header.length; i++)
		message.data[i] = text.charAt(i);
}

void readBuffer(tCAN message) {
	String msgString = "";

	for(int i = 0; i < message.header.length; i++)
		msgString += message.data[i];

	Serial.println(msgString);
}
