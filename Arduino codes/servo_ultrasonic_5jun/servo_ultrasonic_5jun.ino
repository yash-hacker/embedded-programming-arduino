 #include <Servo.h>
#include <Encoder.h>
#define pwm_3 5
#define dir_3 2
#define pwm_4 7
#define dir_4 6
#define trigPin_1 42
#define trigPin_2 36
#define echoPin_1 40
#define echoPin_2 38
#define trigPin_FR 
#define echoPin_FL 
#define trigPin_FR 
#define echoPin_FL 

Servo myservo1;
Servo myservo2;
Encoder enc3(20,21);
Encoder enc4(18,19);

long duration_1,duration_2,cm_1,cm_2,cm_FRR,cm_FLL,r;
int s1_pos = 85,s2_pos = 105;

void setup() {
  myservo1.attach(23);
  myservo2.attach(25);
  myservo1.write(85);
  myservo2.write(105);
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
int pos1 = 980;
int n=0;
 
void loop() {
 //forward_legs();
// check1();                        //getting the values of ultrasonicSensor1 
// check2();
//
// Serial.println(cm_1);
// Serial.println(cm_2);
// Backward_legs();
 //delay(1000);
 check1(); 
 check2();
 checkFR();
 checkFL();
 Serial.println(cm_1);
 Serial.println(cm_2);
 
 if(cm_1>200||cm_2>200)
  {
    servo_check();
    check1();
    check2();
    checkFR();
    checkFL();
  }
 
 if(cm_1<=70 && cm_1>=30)
{
  Serial.println("tilt loop");
  if(tilt()=='R')
  {
    Serial.println("right tilt");
     right_turn();
     
  }
 
  else if(tilt()=='L')
  {
    Serial.println("left tilt");
    left_turn();
    
  }
  
  //forward_legs();
  else
  {
  Backward_legs();
 }
 delay(500);
}

  else if(cm_1<30)
  {  if(n==0)
     {  left_turn();
        left_turn();
        n++;
      }

      //forward_legs();
      delay(500);
      Backward_legs();
      n=0;
}


else if(cm_1>70)
{
  while((cm_1-cm_2)>=8)
  {
    right_turn();
    check1();
    check2();
    
  }
  while(cm_1>70)
  {
    Backward_legs();
    check1();
    check2();
  }
   
}
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
void backward_leg3()
{ 
  newPosition3 = enc3.read();
  long diff3= abs(newPosition3 - oldPosition3);
  while( diff3<=pos)
  {      newPosition3 = enc3.read();
         diff3 = abs(newPosition3 - oldPosition3);
         Serial.println("Backward Leg 3");
//         Serial.println(diff3);
         }
  Serial.println();
  oldPosition3 = newPosition3;
  digitalWrite(pwm_3,LOW);
}

void backward_leg4()
{ 
  newPosition4 = enc4.read();
  long diff4 = abs(newPosition4 - oldPosition4);
  while( diff4<=pos)
  {      newPosition4 = enc4.read();
         diff4 = abs(newPosition4 - oldPosition4);
         Serial.println("Backward Leg 4");
//         Serial.println(diff4);
         }
  Serial.println();
  oldPosition4 = newPosition4;
  digitalWrite(pwm_4,LOW);

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
  delay(500);
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
     
      Serial.println(cm_11);
      if(cm_11>500 && d<5)
  {    d++;
    Serial.println("d"); }
  else
     { 
      c++;
      Serial.println("c");
      sum += cm_11; }
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
 duration_2=pulseIn(echoPin_2,HIGH);
 cm_12= (duration_2/2)*0.0343;
 
 Serial.println(cm_12);
 if(cm_12>500 && d<5)
 {  d++;
  Serial.println("d");
 }
 else
 {  
  c++;
  Serial.println("c");
 sum += cm_12;}
 }
 cm_2= sum/10;
 Serial.println("Final Reading of Sensor 2.");
 Serial.println(cm_2);
 }

 void checkFR()
{ int sum=0,c=0,d=0,cm_FR;
  Serial.println("Sensor FR");
  while(c<10)
  {   digitalWrite(trigPin_FR, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin_FR, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin_FR, LOW);
      duration_1=pulseIn(echoPin_FR,HIGH);
      cm_FR= (duration_1/2)*0.0343;
     
      Serial.println(cm_FR);
      if(cm_FR>500 && d<5)
  {    d++;
    Serial.println("d"); }
  else
     { 
      c++;
      Serial.println("c");
      sum += cm_FR; }
  }
  cm_FRR= sum/10;
      
  
  Serial.println("Final Reading of Sensor F1.");
  Serial.println(cm_1);
  }
   void checkFL()
{ int sum=0,c=0,d=0,cm_FL;
  Serial.println("Sensor FL");
  while(c<10)
  {   digitalWrite(trigPin_FL, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin_FL, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin_FL, LOW);
      duration_1=pulseIn(echoPin_FL,HIGH);
      cm_FL= (duration_1/2)*0.0343;
     
      Serial.println(cm_11);
      if(cm_FL>500 && d<5)
  {    d++;
    Serial.println("d"); }
  else
     { 
      c++;
      Serial.println("c");
      sum += cm_FL; }
  }
  cm_FLL= sum/10;
      
  
  Serial.println("Final Reading of Sensor F2.");
  Serial.println(cm_2);
  }


 
  
 void right_turn()
{ 
  newPosition4 = enc4.read();
  long diff4 = abs(newPosition4 - oldPosition4);
  while( diff4<=pos1)
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
  delay(500);
} 

void left_turn()
{ 
  newPosition3 = enc3.read();
  long diff3 = abs(newPosition3 - oldPosition3);
  while( diff3<=pos1)
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
  delay(500);
}
char tilt()
{ if(cm_FLL<200 && cm_FRR<200)
   r=1;
   else
   r=0;
  if((cm_1-cm_2<-13)||((cm_FLL-cm_FRR<-13)&& r==1))
  return 'L';
  else if((cm_1-cm_2>13)||((cm_FLL-cm_FRR>13)&& r==1))
  return 'R';
  else
  return 'S';
  
}
void servo_check()
{
  Serial.println("servo"); 
  for(s1_pos = 65, s2_pos = 85; s1_pos >= 0,s2_pos >= 20; s1_pos -= 20, s2_pos -= 20) 
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(s1_pos);
    Serial.println(s1_pos); 
    delay(15);
    myservo2.write(s2_pos);
    Serial.println(s2_pos);
    delay(15);
    
    digitalWrite(trigPin_1, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_1, LOW);
    duration_1=pulseIn(echoPin_1,HIGH);
    cm_1= (duration_1/2)*0.0343;
    Serial.println(cm_1); 
    delay(15);
    
    digitalWrite(trigPin_2, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_2, LOW);
    duration_2=pulseIn(echoPin_2,HIGH);
    cm_2= (duration_2/2)*0.0343;
    Serial.println(cm_2); 
    delay(15);
    if(cm_1<200)
    {
    right_turn();
    Serial.println("servo corr right turn"); 
    delay(15);
    myservo1.write(85);
    myservo2.write(105);
    break;
    }
    if(cm_2<200)
    {
    left_turn();
    Serial.println("servo corr left turn");
    delay(15);
    myservo1.write(85);
    myservo2.write(105);
    break;
    }
  
  } 
   Serial.println("Servo out");
}
void sand_dune()
{ if(tilt()=='S'&&(cm_FRR==15&& cm_FLL==15))
{ backward_leg3();
  backward_leg4(); 
  }


  }
