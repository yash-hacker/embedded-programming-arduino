#include <PS2X_lib.h>  //for v1.6
#define dir1 3
#define pwm1 4
#define dir2 6
#define pwm2 7
PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
  pinMode(pwm1,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(13,OUTPUT);
 Serial.begin(57600);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(53,11,10,51, true ,true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
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
  digitalWrite(pwm1,LOW);
  digitalWrite(pwm2,LOW);
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,LOW);
 
}
void loop() {
  ps2x.read_gamepad();
  int lx,ly,rx,ry;
  lx=ps2x.Analog(PSS_LX);
  ly=ps2x.Analog(PSS_LY);
  rx=ps2x.Analog(PSS_RX);
  ry=ps2x.Analog(PSS_RY);
  delay(20);
  if(ps2x.Button(PSB_L1))
  {
    if(ly<110)
    {
      int l=map(ly,110,0,0,255);
      Serial.println("Forward");
      digitalWrite(dir1,HIGH);
      analogWrite(pwm1,l);
      digitalWrite(dir2,LOW);
      analogWrite(pwm2,l);
    }
  else if(ly>140)
  {
    int l=map(ly,140,255,0,255);
    Serial.println("Backward");
    digitalWrite(dir1,LOW);
    analogWrite(pwm1,l);
    digitalWrite(dir2,HIGH);
    analogWrite(pwm2,l);
  }
  else if(lx<110)
  {
    int l=map(lx,110,0,0,255);
    Serial.println("LEFT ");
    digitalWrite(dir1,HIGH);
    analogWrite(pwm1,l);
    digitalWrite(dir2,HIGH);
    analogWrite(pwm2,l);
    
  }
  else if(lx>140)
  {
    int l=map(lx,140,255,0,255);
    Serial.println("Right");
    digitalWrite(dir1,LOW);
    analogWrite(pwm1,l);
    digitalWrite(dir2,LOW);
    analogWrite(pwm2,l);
  }
  else
  {
    digitalWrite(pwm1,LOW);
    digitalWrite(pwm2,LOW);
  }
  }
  else
  {
    digitalWrite(pwm1,LOW);
    digitalWrite(pwm2,LOW);
  }
}
