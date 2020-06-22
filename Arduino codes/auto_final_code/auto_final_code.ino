
#include <Encoder.h>
#define pwm_3 5
#define dir_3 2
#define pwm_4 7
#define dir_4 6
#define trigPin_1 42
#define trigPin_2 36
#define echoPin_1 40
#define echoPin_2 38

Encoder enc3(20,21);
Encoder enc4(18,19);

long duration_1,duration_2,cm_1,cm_2;

void setup() {
//  pinMode(pwm_1, OUTPUT);
//  pinMode(dir_1, OUTPUT);
//  pinMode(pwm_2, OUTPUT);
//  pinMode(dir_2, OUTPUT);
  pinMode(pwm_3, OUTPUT);
  pinMode(dir_3, OUTPUT);
  pinMode(pwm_4, OUTPUT);
  pinMode(dir_4, OUTPUT);
//  digitalWrite(dir_1,HIGH);
//  digitalWrite(dir_2,LOW);
  digitalWrite(dir_3,LOW);
  digitalWrite(dir_4,HIGH);
  //digitalWrite(pwm_1,LOW);
  //digitalWrite(pwm_2,LOW);
  digitalWrite(pwm_3,LOW);
  digitalWrite(pwm_4,LOW);
  pinMode(trigPin_1,OUTPUT);
  pinMode(echoPin_1,INPUT);
  pinMode(trigPin_2,OUTPUT);
  pinMode(echoPin_2,INPUT);
  Serial.begin(9600);
  
}

long oldPosition1  = 0,oldPosition2  = 0,oldPosition3  = 0,oldPosition4  = 0;
long newPosition1,newPosition2, newPosition3, newPosition4;
int speedM = 180;
int pos = 740;
int n=0;
void loop() {
 //forward_legs();
 check1();                        //getting the values of ultrasonicSensor1 
 check2();
 Serial.println(cm_1);
 Serial.println(cm_2);
 Backward_legs();
 check1(); 
 check2();
 while(cm_1<=50 && cm_1>=20)
{
  while(tilt()=='R')
  left_turn();
  while(tilt()=='L')
  right_turn();
  //forward_legs();
  delay(1000);
  Backward_legs();
  check1();
  check2();
}
while(cm_1<20)
{  if(n==0)
   {right_turn();
    right_turn();
    n++;}

    //forward_legs();
    delay(1000);
    Backward_legs();
    check1();
    check2();
   
}
n=0;

while(cm_2>50)
{
  while((cm_1-cm_2)>=0)
  {
    left_turn();
    check1();
    check2();
  }

  Backward_legs();
  check1();
  check2();  
}
//while(cm_2>50)
//{ if(n==0)
//  {left_turn();
//   left_turn();
//   n++;}
//  //forward_legs(); 
//  delay(1000);
//  Backward_legs();
//  check1();
//  check2();
//}
//n=0;
//}



//void forward_legs()
//{ 
//  analogWrite(pwm_1,speedM);
//  analogWrite(pwm_2,speedM);
//  newPosition1 = enc1.read();
//  newPosition2 = enc2.read();
//  long diff1 = abs(newPosition1 - oldPosition1);
//  long diff2 = abs(newPosition2 - oldPosition2);
//  while( diff1<=pos || diff2<=pos)
//  {      newPosition1 = enc1.read();
//         newPosition2 = enc2.read();
//         diff1 = abs(newPosition1 - oldPosition1);
//         diff2 = abs(newPosition2 - oldPosition2);
//         Serial.println("Forward Legs");
//         Serial.println(diff1);
//         Serial.println(diff2);
//         if(diff1>pos)
//         {
//         digitalWrite(pwm_1,0);
//         Serial.println("Motor 1 Done");
//         }
//         if(diff2>pos)
//         {
//         digitalWrite(pwm_2,0);
//         Serial.println("Motor 2 done");
//         }
//  }
//  Serial.println();
//  oldPosition1 = newPosition1;
//  oldPosition2 = newPosition2;
//}

void Backward_legs()
{ 
  analogWrite(pwm_3,speedM);
  analogWrite(pwm_4,speedM);
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
  oldPosition3 += pos;
  oldPosition4 += pos;
  delay(1000);
}


void check1()
{ int sum=0,c=0,d=0,cm_11;
  Serial.println("Sensor 1");
  while(c<10)
  {   digitalWrite(trigPin_1, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin_1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin_1, LOW);
      duration_1=pulseIn(echoPin_1,HIGH);
      cm_11= (duration_1/2)*0.0343;
     
      Serial.print(cm_11);
      if(cm_11>500 && d<5)
      d++;
      else
      c++;
      sum += cm_11;
  }
  cm_1= sum/10;
  Serial.println("Final Reading of Sensor 1.");
  Serial.println(cm_1);
  }
 
 void check2()
 {
  int sum=0,c=0,d=0,cm_12;
  Serial.println("Sensor 2");
  while(c<10)
  {digitalWrite(trigPin_2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);
 duration_1=pulseIn(echoPin_2,HIGH);
 cm_12= (duration_1/2)*0.0343;
 
 Serial.print(cm_12);
 if(cm_12>500 && d<5)
 d++;
 else
 c++;
 sum += cm_12;
 }
 cm_2= sum/10;
 Serial.println("Final Reading of Sensor 2.");
 Serial.println(cm_2);
 }
 
 void right_turn()
{ 
  check1();
  check2();
  newPosition4 = enc4.read();
  long diff4 = abs(newPosition4 - oldPosition4);
  while( diff4<=pos)
  {      newPosition4 = enc4.read();
         analogWrite(pwm_4,speedM);
         diff4 = abs(newPosition4 - oldPosition4);
         Serial.println("Leg 4 trying to turn right ");
         Serial.println(diff4);
//         if(diff4>pos)
//         {
//         digitalWrite(pwm_4,0);
//         Serial.println("Right Turn");
//         }
  }
  digitalWrite(pwm_4,0);
  Serial.println();
  oldPosition4 += pos;
  delay(1000);
} 

void left_turn()
{ 
  check1();
  check2();
  newPosition3 = enc3.read();
  long diff3 = abs(newPosition3 - oldPosition3);
  while( diff3<=pos)
  {      newPosition3 = enc3.read();
         analogWrite(pwm_3,speedM);
         diff3 = abs(newPosition3 - oldPosition3);
         Serial.println( "Leg 3 trying to turn left");
         Serial.println(diff3);
//         if(diff3>pos)
//         {
//         digitalWrite(pwm_3,0);
//         Serial.println("Left Turn");
//         }
         
  }
  digitalWrite(pwm_3,0);
  Serial.println();
  oldPosition3 += pos;
  delay(1000);
}
char tilt()
{
  if(cm_1-cm_2<-5)
  return 'L';
  else if(cm_1-cm_2>5)
  return 'R';
  else
  return 'S';
}
