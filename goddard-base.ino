// -*- mode: C++ -*-
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//This pin is used to set the nRF24 to standby (0) or active mode (1)
#define pinCE 8

//This pin is used to tell the nRF24 whether the SPI communication
// is a command or message to send out
#define pinCSN 10
uint8_t frame[] = "B090H"; // Packet format B[R][G][B][Emote].
// Create your nRF24 object or wireless SPI connection
RF24 wirelessSPI(pinCE, pinCSN);
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pAddress = 0xB00B1E5000LL;

void setup()  
{
  //start serial to communicate process
  Serial.begin(9600);
  //Start the nRF24 module
  wirelessSPI.begin();
  // Ensure autoACK is enabled so rec sends ack packet
  // to let you know it got the transmit packet payload
  wirelessSPI.setAutoAck(1);
  // Allow optional ack payloads
  wirelessSPI.enableAckPayload();
  wirelessSPI.setPALevel(RF24_PA_MAX);
  wirelessSPI.setDataRate(RF24_250KBPS);
  // pipe address that we will communicate over,
  // must be the same for each nRF24 module
  wirelessSPI.openWritingPipe(pAddress);
  //transmitter so stop listening for data
  wirelessSPI.stopListening();
  //use random ADC value to seed random number algorithm
  randomSeed(analogRead(0));
}

void loop() {
  delay(500);
  while(Serial.available() > 0) {
      uint8_t inByte = Serial.read();
      if(inByte == 'B') {
          Serial.readBytes(&frame[1],4);
          if(frame[1] < '0' || frame[1] > '9') break;
          if(frame[2] < '0' || frame[2] > '9') break;
          if(frame[3] < '0' || frame[3] > '9') break;
          if(frame[4] < 'A' || frame[4] > 'Z' || frame[4] == 'B') break;
          //if the send fails let the user know over serial monitor
          Serial.write((char*)frame);
          if (wirelessSPI.write( frame, 5 )){
              Serial.write(".");
          } else {
              Serial.write("!");
          }
      }
  }
}
