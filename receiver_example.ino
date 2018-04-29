#include<SPI.h>
//#include<nRF24L01.h>
#include<RF24.h>
const uint64_t pipe[1]= {0xF0F0F0F0E1LL};
RF24 radio(7,8);
typedef struct {
  int x;
  int y;
  } positions;

positions rec;
//int ack[1] = {990};
void setup()
{
  Serial.begin(57600);
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1,pipe[0]);
  radio.startListening();
  radio.setRetries(15,15);
}
void loop()
{
   //Serial.println(radio.available());
  //radio.writeAckPayload(1,ack,sizeof(ack));
  if(radio.available())
  {
    //Serial.println(radio.available());
    //radio.writeAckPayload(1,ack,sizeof(ack));
    if(radio.available())
    {
      radio.read(&rec,sizeof(rec));
      radio.writeAckPayload(1,&rec,sizeof(rec));
      //Serial.print("integer got is : ");
      //Serial.println(String(rec.x) + " + " + String( rec.y) );
      Serial.print(rec.x);
      Serial.print(' ');
      Serial.println(rec.y);
    }
    else
    {Serial.println("failed to receive the message");}
  }
}
