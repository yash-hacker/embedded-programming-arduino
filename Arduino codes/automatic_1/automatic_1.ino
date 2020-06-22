#include <Encoder.h>
#define aspeed_3 230
#define aspeed_1 230
#define aspeed_2 230
#define aspeed_4 230
//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you conect the controller,
//or call config_gamepad(pins) again after connecting the controller.

byte slow_speed_1 = 210;
byte slow_speed_3 = 255;
byte right;
byte left;
int rev_pos_1=260;
int rev_pos_3=260;
int stop_pos_1=280;
int stop_pos_3=280;
long pos1=0;
long pos2=0;
long pos3=0;
long pos4=0;
long last_pos1=0;
long last_pos2=0;
long last_pos3=0;
long last_pos4=0;
void read_sensor1();
void read_sensor2();
void shifting();
void move_right_dir();
void move_left_dir();
#define trig1 9
#define echo1 10
#define trig2 11
#define echo2 12
unsigned long duration1=0;
unsigned long distance1=0;
unsigned long duration2=0;
unsigned long distance2=0;
int diff=0;
#define pwm_1 5
#define dir_1 44
#define pwm_2 6
#define dir_2 45
#define pwm_3 7
#define dir_3 42
#define pwm_4 8
#define dir_4 43
Encoder enc1(3,2);
Encoder enc2(18,22);
Encoder enc3(19,20);
Encoder enc4(21,15);

void setup() {
  Serial.begin(57600);
  pinMode(pwm_1, OUTPUT);
  pinMode(dir_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  pinMode(dir_2, OUTPUT);
  pinMode(pwm_3, OUTPUT);
  pinMode(dir_3, OUTPUT);
  pinMode(pwm_4, OUTPUT);
  pinMode(dir_4, OUTPUT);
  digitalWrite(dir_1,HIGH);
  digitalWrite(dir_2,LOW);
  digitalWrite(dir_3,LOW);
  digitalWrite(dir_4,HIGH);
  digitalWrite(pwm_1,LOW);
  digitalWrite(pwm_2,LOW);
  digitalWrite(pwm_3,LOW);
  digitalWrite(pwm_4,LOW);

  pinMode(trig1, OUTPUT);
  pinMode(echo1,INPUT);
   pinMode(trig2, OUTPUT);
  pinMode(echo2,INPUT);
}

void loop()
{
     digitalWrite(dir_1,HIGH); 
     digitalWrite(dir_2,LOW); 
     digitalWrite(dir_3,LOW); 
     digitalWrite(dir_4,HIGH); 

     // position check---------------------
    right=1;
    left=1;
    read_sensor1();
    read_sensor2();
    diff=distance1-distance2;
    if(distance1<40 && distance2<40)
    { 
      Serial.println("within 30");
      if(diff>4)
      move_left_dir();
      else if(diff<-3)
      move_right_dir();
      
    }
    else if((distance1>=40 && distance2>=40)&&(distance1<=100 && distance2<=100))
    { Serial.println("shifting between 30 & 100");
      shifting();   
    }
     else
     {
      while(distance1>100&& distance2>100)
      {
         Serial.println("beyond 100");
      move_left_dir();
      read_sensor1();
      read_sensor2();
      }
     }
     //---------------------------------
//right
      if(right==1)
      {
        Serial.println("right");
        move_right_dir();
      }
      last_pos2=abs(enc2.read());
      last_pos3=abs(enc3.read());
      
      //------------------------------------------------------------
      //left
      
     if(left==1)
     {
      Serial.println("left");
       move_left_dir();
     }
      last_pos1=abs(enc1.read());
      last_pos4=abs(enc4.read());
}

 void shifting()
 {
      move_left_dir();
      move_left_dir();
      
      while(distance1>20)
      {
        Serial.println("greater than 20 shifting");
        move_right_dir();
        move_left_dir();
        read_sensor1();
        read_sensor2();
      }
       read_sensor1();
       read_sensor2();
      diff=distance1-distance2;
      while(diff>5)
      {  Serial.println("right correction");
        move_right_dir();
        read_sensor1();
        read_sensor2();
        diff=distance1-distance2;
      }
 }
 void move_right_dir()
 {    
      Serial.println("right direction");
      last_pos1=abs(enc1.read());
      last_pos4=abs(enc4.read());
     analogWrite(pwm_1,aspeed_1);
     analogWrite(pwm_2,0);
     analogWrite(pwm_4,aspeed_4);
     analogWrite(pwm_3,0);
     pos1=abs(enc1.read());
     pos4=abs(enc4.read());
     while(((pos1-last_pos1)<stop_pos_1) || ((pos4-last_pos4)<stop_pos_3) )
     {
         pos1=abs(enc1.read());
         pos4=abs(enc4.read());
          
         if(!((pos1-last_pos1)<stop_pos_1))
         {
          analogWrite(pwm_1,0);
         }
         if(!((pos4-last_pos4)<stop_pos_3))
         {
          analogWrite(pwm_4,0);
         }
     }
      analogWrite(pwm_1,0);
      analogWrite(pwm_2,0);
      analogWrite(pwm_3,0);
      analogWrite(pwm_4,0);
      delay(200);
      
 }
 void move_left_dir()
 {   Serial.println("left direction");
     last_pos2=abs(enc2.read());
     last_pos3=abs(enc3.read());
     analogWrite(pwm_2,aspeed_2);
     analogWrite(pwm_1,0);
     analogWrite(pwm_3,aspeed_3);
     analogWrite(pwm_4,0);
     pos2=abs(enc2.read());
     pos3=abs(enc3.read());
     while(((pos2-last_pos2)<stop_pos_1) || ((pos3-last_pos3)<stop_pos_3) )
     {
         pos2=abs(enc2.read());
         pos3=abs(enc3.read());
         
         if(!((pos2-last_pos2)<stop_pos_1))
         {
          analogWrite(pwm_2,0);
         }
         if(!((pos3-last_pos3)<stop_pos_3))
         {
          analogWrite(pwm_3,0);
         }
     }
      analogWrite(pwm_1,0);
      analogWrite(pwm_2,0);
      analogWrite(pwm_3,0);
      analogWrite(pwm_4,0);
      delay(200);
     
 }
void read_sensor1()
{
    digitalWrite(trig1,LOW);
    delayMicroseconds(2);
    digitalWrite(trig1,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1,LOW);
    duration1=pulseIn(echo1,HIGH);
    distance1=0.034*(duration1/2);
    Serial.println(distance1);
    
 }
 void read_sensor2()
{
    digitalWrite(trig2,LOW);
    delayMicroseconds(2);
    digitalWrite(trig2,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2,LOW);
    duration2=pulseIn(echo2,HIGH);
    distance2=0.034*(duration2/2);
    Serial.println(distance2);
    
 } 

