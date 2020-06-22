#include <PS2X_lib.h>
#include <Encoder.h>
#define pwm_1 11
#define dir_1 10
#define pwm_2 9
#define dir_2 8
#define pwm_3 7
#define dir_3 6
#define pwm_4 5
#define dir_4 4
PS2X ps2x;
Encoder enc1(3,2);
Encoder enc2(18,22);
Encoder enc3(19,20);
Encoder enc4(21,15);
int error = 0; 
byte type = 0;
byte vibrate = 0;
#define aspeed_1 170
#define aspeed_2 170
#define aspeed_3 170
#define aspeed_4 170
int stop_pos_1=350;
int stop_pos_2=350;
int stop_pos_3=350;
int stop_pos_4=350;
long pos1=0;
long pos2=0;
long pos3=0;
long pos4=0;
long last_pos1=0;
long last_pos2=0;
long last_pos3=0;
long last_pos4=0;
void backward_legs();
void forward_legs();
void move_right_dir();
void move_left_dir();
void forward_leg1();
void forward_leg2();
void backward_leg3();
void backward_leg4();
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
  digitalWrite(dir_4,HIGH);
  digitalWrite(pwm_1,LOW);
  digitalWrite(pwm_2,LOW);
  digitalWrite(pwm_3,LOW);
  digitalWrite(pwm_4,LOW);
  error = ps2x.config_gamepad(53,46,44,51,false,false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 Serial.begin(57600);
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
}

long oldPosition1  = 0,oldPosition2  = 0,oldPosition3  = 0,oldPosition4  = 0;
long newPosition1,newPosition2, newPosition3, newPosition4;
int speedM = 125;
int pos = 384;
int dly= 500;

void loop() {
  if (error == 1) //skip loop if no controller found
    return;
else{
delay(3000);
ps2x.read_gamepad(false, vibrate);
if(ps2x.ButtonPressed(PSB_GREEN)) //one by one motion 
{
analogWrite(pwm_1,speedM);
forward_leg1();
delay(dly);
analogWrite(pwm_2,speedM);
forward_leg2();
delay(dly);
analogWrite(pwm_3,speedM);
backward_leg3();
delay(dly);
analogWrite(pwm_4,speedM);
backward_leg4();
delay(dly);
Serial.println("green");
}
if(ps2x.ButtonPressed(PSB_PINK)) // hop motion
{ 
  analogWrite(pwm_1,speedM);
  analogWrite(pwm_2,speedM);
  forward_legs();
  delay(600);
  analogWrite(pwm_3,speedM);
  analogWrite(pwm_4,speedM);
  backward_legs();
  delay(600);
  
Serial.println("pink");
}
if(ps2x.ButtonPressed(PSB_BLUE)) //side motion
{
 move_right_dir();
 delay(500); 
 move_left_dir();
 delay(500);
 
Serial.println("blue");
}
if(ps2x.ButtonPressed(PSB_RED)) //only backward legs
{
 backward_legs();
 delay(600);
 
Serial.println("RED");
}
if(ps2x.Button(PSB_PAD_DOWN))//Leg 2
{
analogWrite(pwm_2,speedM);

forward_leg2();}
if(ps2x.Button(PSB_PAD_LEFT))
{//Leg 3
  analogWrite(pwm_3,speedM);
  backward_leg3();}
if(ps2x.Button(PSB_PAD_RIGHT))
{//Leg 4
  analogWrite(pwm_4,speedM);
  backward_leg4();}
if(ps2x.Button(PSB_PAD_UP))
{//Leg 1
  analogWrite(pwm_1,speedM);
  forward_leg1();}
}
}

void forward_leg1()
{ 
  newPosition1 = enc1.read();
  long diff1 = abs(newPosition1 - oldPosition1);
  while( diff1<=pos)
  {      
         newPosition1 = enc1.read();
         diff1 = abs(newPosition1 - oldPosition1);
         Serial.println("Forward Leg 1");
//         Serial.println(diff1);
         }
  Serial.println();
  oldPosition1 = newPosition1;
  digitalWrite(pwm_1,LOW);
  
}

void forward_leg2()
{  
  newPosition2 = enc2.read();
  long diff2 = abs(newPosition2 - oldPosition2);
  while( diff2<=pos)
  {      newPosition2 = enc2.read();
         diff2 = abs(newPosition2 - oldPosition2);
         Serial.println("Forward Leg 2");
//         Serial.println(diff2);
         }
  Serial.println();
  oldPosition2 = newPosition2;
  digitalWrite(pwm_2,LOW);
}


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
     
     while(((pos1-last_pos1)<stop_pos_1) || ((pos4-last_pos4)<stop_pos_4) )
     {
         pos1=abs(enc1.read());
         pos4=abs(enc4.read());
         
         if(!((pos1-last_pos1)<stop_pos_1))
         {
          Serial.println("stop1");
          analogWrite(pwm_1,0);
         }
         if(!((pos4-last_pos4)<stop_pos_4))
         {
          Serial.println("stop4");
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
 {   
     Serial.println("left direction");
     last_pos2=abs(enc2.read());
     
     last_pos3=abs(enc3.read());
     analogWrite(pwm_2,aspeed_2);
     analogWrite(pwm_1,0);
     analogWrite(pwm_3,aspeed_3);
     analogWrite(pwm_4,0);
     pos2=abs(enc2.read());
     pos3=abs(enc3.read());
     while(((pos2-last_pos2)<stop_pos_2) || ((pos3-last_pos3)<stop_pos_3) )
     {
         pos2=abs(enc2.read());
         pos3=abs(enc3.read());
         
         if(!((pos2-last_pos2)<stop_pos_2))
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
