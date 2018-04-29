#include<SPI.h>
#include<RF24.h>

const uint64_t pipe[1]= {0xF0F0F0F0E1LL};
RF24 radio(7,8);


typedef struct {
  int x;
  int y;
  } positions;



// map motor poles to Arduino pins
#define motor1out1 19 
#define motor1out2 2
#define motor2out1 16
#define motor2out2 4
#define motor3out1 17
#define motor3out2 18

// map L293d motor enable pins to Arduino pins
#define enable1 3
#define enable2 5
#define enable3 6

#define M1_MAX_SPEED 100
#define M2_MAX_SPEED 100

int mspeed = 110;
positions pos;

void setup() {
     Serial.begin(9600);   
   // set mapped L293D motor1 and motor 2 enable pins on Arduino to output (to turn on/off motor1 and motor2 via L293D)
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(enable3, OUTPUT);


  // set mapped motor poles to Arduino pins (via L293D)
  pinMode( motor1out1 , OUTPUT);
  pinMode( motor1out2, OUTPUT);
  pinMode( motor2out1, OUTPUT);
  pinMode( motor2out2 , OUTPUT);
  pinMode( motor3out1, OUTPUT);
  pinMode( motor3out2 , OUTPUT);
  motorspeed(0, 0,0);

  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1,pipe[0]);
  radio.startListening();
  radio.setRetries(15,15);
  
}




void loop() {

        pos = getRadio();


 Serial.println("POS.X= " + String(pos.x) );
//mspeed = map(sqrt(pos.x),0,sqrt(1024),0,255) ;
   Serial.println("POS.X= " + String(mspeed) );
  // Set Motor Speed for all 3 motors
  motorspeed(mspeed,mspeed,mspeed);
 
  // spin both motors in one direction
  Serial.print("BOTH MOTORS FORWARD @ SPEED: ");
  Serial.println(mspeed);
  motorclock(1);
  motorclock(3);
  motorclock(2);
  delay(2000);

  // stop both motors
  //Serial.println("BOTH MOTORS STOP FOR 2 SEC."); 
 motorstop(1);
 motorstop(2);
 motorstop(3);
   delay(2000);

  motorclock(1);
  motorstop(3);
  motoranticlock(2);
 delay(2000);

 motorstop(1);
 motorstop(2);
 motorstop(3);
   delay(2000);


  // spin both motors in one direction
  //Serial.print("BOTH MOTORS Backward @ SPEED: ");
  //Serial.println(mspeed);
  //motoranticlock(1);
  //motoranticlock(2);
  //motoranticlock(3);
   //delay(2000);

// stop both motors
  //Serial.println("BOTH MOTORS STOP FOR 2 SEC."); 
  //motorstop(1);
  //motorstop(2);
  //motorstop(3);
//delay(2000);
 
 // if(Serial.available())
  //  mspeed = Serial.parseInt();

}

// Stop motor Function
// motor 1,2,3
void motorstop(int motor){
  if(motor == 1){
    digitalWrite(motor1out1,LOW);
    digitalWrite(motor1out2,LOW);  
  }
  else if (motor == 2){
    digitalWrite(motor2out1,LOW);
    digitalWrite(motor2out2,LOW);  
  }
  else if (motor == 3){
    digitalWrite(motor3out1,LOW);
    digitalWrite(motor3out2,LOW);
  }

}

// Spin motor function assuming clockwise rotation
// motor 1,2,3
void motorclock(int motor){
  if(motor == 1){
    digitalWrite(motor1out1,HIGH);
    digitalWrite(motor1out2,LOW);  
  }
  else if (motor == 2){
      digitalWrite(motor2out1,HIGH);
    digitalWrite(motor2out2,LOW);  
  }
  else if (motor == 3){
    digitalWrite(motor3out1,HIGH);
    digitalWrite(motor3out2,LOW);
  }
}

// Spin motor function assuming anticlockwise rotation
// motor 1,2,3
void motoranticlock(int motor){
  if(motor == 1){
    digitalWrite(motor1out1,LOW);
    digitalWrite(motor1out2,HIGH);  
  }
  else if (motor == 2){
      digitalWrite(motor2out1,LOW);
    digitalWrite(motor2out2,HIGH);  
  }
  else if (motor == 3){
    digitalWrite(motor3out1,LOW);
    digitalWrite(motor3out2,HIGH);
  }
}

// Set motors to desirable speeds
void motorspeed(int m1speed, int m2speed,int m3speed){
  analogWrite(enable1,m1speed);
  analogWrite(enable2,m2speed);
  analogWrite(enable3,m3speed);
}


positions getRadio() {
  if(radio.available())
    {
    positions rec;
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
      return rec;
    }
    else
    {
      Serial.println("failed to receive the message");
      return pos;
     }
    }
}

  
