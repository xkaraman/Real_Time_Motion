/* ARTEMIS // tekto_wheel project // 2017-2018
 *  
 *  nRFCommunication code for the controller node
 *  *robot node is another file
 *  
 *  using SPI comm for the nRF24L01 module
 *  connected to the DPins 7,8 of arduino
 *  
 *  author : cLupi
 *  try: 1st 
 *  date: 29/11/17
 *  
 *  ToDo:
 *  enable auto ACK and default send receive methods for nRF
 *  repetitive packets to be sent until the right ACK respond comes.
 *  custom ACK Payloads?
 */

 
#include <SPI.h>
#include "RF24.h"



RF24 radio(7,8);

byte addr[][6] = {"cNode","tNode"}; //Tx & Rx addresses

byte gotPack=0;     //incoming bytes

void setup() {
  Serial.begin(9600);
  Serial.println("This Node started");

  radio.begin();
  radio.openWritingPipe(addr[0]);
  radio.openReadingPipe(1,addr[1]);
  
  radio.startListening(); 
}

void loop() {
  
  if(Serial.available()){  //Console input
    char ch=Serial.read(); //Serial.readString();
    radio.stopListening();
    radio.write(&ch,sizeof(char));
    radio.startListening();
  }
  if(radio.available()){   //remote node nRF response handling
    radio.read(&gotPack,1);
    Serial.print("got response: ");
    Serial.println((char)gotPack);
  }
}
