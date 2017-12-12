#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int msg[1] = {1};
int rec[1] = {5};
bool stat = true;
RF24 radio(7,8);
const uint64_t pipe[1] = {0xF0F0F0F0E1LL};
 
void setup()
{
  Serial.begin(57600);
  radio.begin();
  delay(1000);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openWritingPipe(pipe[0]);
  radio.setRetries(15,15);
 }

 
void loop()
{
  if(stat)
  {
    radio.stopListening();
    if(radio.write(msg,sizeof(msg)))
    {
      Serial.print( msg[0] );
      Serial.println("  transmitted successfully !!");

      if(radio.isAckPayloadAvailable())
      {
        radio.read(rec,sizeof(rec));
       Serial.print("received ack payload is : ");
        Serial.println(rec[0]);
      }
      else
      {
        stat = false; //doing this completely shuts down the transmitter if an ack payload is not received !!
        Serial.println("status has become false so stop here....");
      }
      
      msg[0]+=3;;
    if(msg[0]>=100)
      {msg[0]=1;}
    }
    else
      {
        Serial.println("failed tx...");
      }
  }

  delay(100);
}
