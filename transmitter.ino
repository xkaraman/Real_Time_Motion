#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int msg[1] = {1};
int rec[1] = {5};
bool stat = true;
RF24 radio(7,8);
unsigned long time;
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

typedef struct {
  int x;
  int y;
  } positions;

positions pos;

 
void loop()
{
  if(stat)
  {
    radio.stopListening();
    
    pos.x=analogRead(A0);
    pos.y=analogRead(A1);

   // pos.x = map(x,0,1023,-510,514);
   // pos.y = map(y,0,1023,-510,514);

    Serial.println("X= "+ String(pos.x) + " Y= "+ String(pos.y) );
    time=millis();
    
    if( radio.write(&pos,sizeof(pos) ) ){
      //Serial.print( msg[0] );
      Serial.println("  transmitted successfully !!");
      if(radio.isAckPayloadAvailable()){
       radio.read(&pos,sizeof(pos));
       Serial.print("received ack payload is : ");
       Serial.println("X= "+ String(pos.x) + " Y= "+ String(pos.y) );
      //analogWrite(A2,pos.x);
      }
    }
    else {
        Serial.println("failed tx...");
      }
      
    time=millis()-time;
    Serial.println("Time needed is " + String(time) +  " ms");
  }

  //delay(10);
}
