/* ARTEMIS // tekto_wheel project // 2017-2018
 *  
 *  nRFCommunication code for the robot node
 *  *controller node is another file
 *  
 *  using SPI comm for the nRF24L01 module
 *  connected to the DPins 7,8 of arduino
 *  
 *  author : cLupi
 *  try: 1st 
 *  date: 29/11/17
 */
 
#include <SPI.h>
#include "RF24.h"



RF24 radio(7,8);

byte addr[][6] = {"cNode","tNode"}; //Tx & Rx addresses

byte gotPack=0; //incoming bytes

void setup() {
  Serial.begin(9600);
  Serial.println("This Node started");

  radio.begin();
  radio.openWritingPipe(addr[1]);
  radio.openReadingPipe(1,addr[0]);
  
  radio.startListening(); 
}

void loop() {
  if(radio.available()){
    radio.read(&gotPack,1);
    gotPack+=1;
    radio.stopListening();
    radio.write(&gotPack,1);  //responding with the nesxt ascii character
    radio.startListening();
  }
}
