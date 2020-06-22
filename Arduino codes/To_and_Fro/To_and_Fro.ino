
#include <Encoder.h>
#define pwm_1 11
#define dir_1 10
#define pwm_2 9
#define dir_2 8
#define pwm_3 7
#define dir_3 6
#define pwm_4 5
#define dir_4 4
Encoder enc1(3,2);
Encoder enc2(18,22);
Encoder enc3(19,20);
Encoder enc4(21,15);

void setup() {
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
  digitalWrite(dir_3,HIGH);
  digitalWrite(dir_4,LOW);
  digitalWrite(pwm_1,LOW);
  digitalWrite(pwm_2,LOW);
  digitalWrite(pwm_3,LOW);
  digitalWrite(pwm_4,LOW);
  Serial.begin(9600);
}

long oldPosition1  = 0,oldPosition2  = 0,oldPosition3  = 0,oldPosition4  = 0;
long newPosition1,newPosition2, newPosition3, newPosition4;
int speedM = 250;
int pos = 15;
void loop() {
analogWrite(pwm_1,speedM);
analogWrite(pwm_2,speedM);
forward_legs();
analogWrite(pwm_1,speedM);
analogWrite(pwm_2,speedM);
forward_legs();
delay(500);
analogWrite(pwm_3,speedM);
analogWrite(pwm_4,speedM);
backward_legs();
analogWrite(pwm_3,speedM);
analogWrite(pwm_4,speedM);
backward_legs();
delay(500);
}

void forward_legs()
{ 
  newPosition1 = enc1.read();
  newPosition2 = enc2.read();
  long diff1 = abs(newPosition1 - oldPosition1);
  long diff2 = abs(newPosition2 - oldPosition2);
  while( diff1<=pos || diff2<=pos)
  {      newPosition1 = enc1.read();
         newPosition2 = enc2.read();
         diff1 = abs(newPosition1 - oldPosition1);
         diff2 = abs(newPosition2 - oldPosition2);
         Serial.println("Forward Legs");
         Serial.println(diff1);
         Serial.println(diff2);
         if(diff1>pos)
         {
         digitalWrite(pwm_1,0);
         Serial.println("Motor 1 Done");
         }
         if(diff2>pos)
         {
         digitalWrite(pwm_2,0);
         Serial.println("Motor 2 done");
         }
  }
  Serial.println();
  oldPosition1 = newPosition1;
  oldPosition2 = newPosition2;
  digitalWrite(dir_1,!digitalRead(dir_1));
  digitalWrite(dir_2,!digitalRead(dir_2));
}

void backward_legs()
{
  newPosition3 = enc3.read();
  newPosition4 = enc4.read();
  long diff3 = abs(newPosition3 - oldPosition3);
  long diff4 = abs(newPosition4 - oldPosition4);
  while(diff3<=pos || diff4<=pos)
  {
         newPosition3 = enc3.read();
         newPosition4 = enc4.read();
         diff3 = abs(newPosition3 - oldPosition3);
         diff4 = abs(newPosition4 - oldPosition4);
         Serial.println("Backward Legs");
         Serial.println(diff3);
         Serial.println(diff4);
         if(diff3>pos)
         {
         digitalWrite(pwm_3,0);
         Serial.println("Motor 3 Done");
         }
         if(diff4>pos)
         {
         digitalWrite(pwm_4,0);
         Serial.println("Motor 4 Done");
         }
  }
  Serial.println();
  oldPosition3 = newPosition3;
  oldPosition4 = newPosition4;
  digitalWrite(dir_3,!digitalRead(dir_3));
  digitalWrite(dir_4,!digitalRead(dir_4)); 
}
