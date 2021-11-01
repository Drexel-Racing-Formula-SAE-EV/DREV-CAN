#include "Arduino.h"
#include <SPI.h>

#include <drev_can.h>

#define ID 0x631

#define SEND 1
#define RECEIVE 2

#define MODE RECEIVE

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

            Serial.println(canBus.sendMsgBuf(ID, 0, 1, message));

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

void writeBuffer(String text, int length, char message[]) {
	for(int i = 0; i < length; i++)
		message[i] = text.charAt(i);
}

void printBuffer(char message[], int length) {
	String msgString = "";

	for(int i = 0; i < length; i++)
		msgString += message[i];

	Serial.println(msgString);
}

// demo: CAN-BUS Shield, send data
// loovee@seeed.cc

// #include <mcp_can.h>
// #include <SPI.h>

// /*SAMD core*/
// #ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
//   #define SERIAL SerialUSB
// #else
//   #define SERIAL Serial
// #endif

// // the cs pin of the version after v1.1 is default to D9
// // v0.9b and v1.0 is default D10
// const int SPI_CS_PIN = 10;

// MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

// void setup()
// {
//     SERIAL.begin(115200);

//     while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
//     {
//         SERIAL.println("CAN BUS Shield init fail");
//         SERIAL.println(" Init CAN BUS Shield again");
//         delay(100);
//     }
//     SERIAL.println("CAN BUS Shield init ok!");
// }

// unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// void loop()
// {
//     // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
//     stmp[7] = stmp[7]+1;
//     if(stmp[7] == 100)
//     {
//         stmp[7] = 0;
//         stmp[6] = stmp[6] + 1;
        
//         if(stmp[6] == 100)
//         {
//             stmp[6] = 0;
//             stmp[5] = stmp[6] + 1;
//         }
//     }
    
//     Serial.println(CAN.sendMsgBuf(0x00, 0, 8, stmp));
//     delay(100);                       // send data per 100ms
// }

// // END FILE
