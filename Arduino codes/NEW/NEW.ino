#include <PS2X_lib.h>  //for v1.6
#define FL 5
#define FLD 44
#define FR 6
#define FRD 45
#define BR 7
#define BRD 42
#define BL 8
#define BLD 43
int d=1000;PS2X ps2x; // create PS2 Controller Class
int c=0;
//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
int k=50;
byte type = 0;
byte vibrate = 0;

void setup(){
    pinMode(BR,OUTPUT);
  pinMode(FR,OUTPUT);
  pinMode(BRD,OUTPUT);
  pinMode(FRD,OUTPUT);
  pinMode(BL,OUTPUT);
  pinMode(FL,OUTPUT);
  pinMode(BLD,OUTPUT);
  pinMode(FLD,OUTPUT);
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
  digitalWrite(BR,LOW);
digitalWrite(FR,LOW);
digitalWrite(BL,LOW);
digitalWrite(FL,LOW);
digitalWrite(BRD,LOW);
digitalWrite(FRD,LOW);
digitalWrite(BLD,LOW);
digitalWrite(FLD,LOW);
 
}
void loop() {
  ps2x.read_gamepad();
  int lx,ly,rx,ry;
  lx=ps2x.Analog(PSS_LX);
  ly=ps2x.Analog(PSS_LY);
  rx=ps2x.Analog(PSS_RX);
  ry=ps2x.Analog(PSS_RY);
  
  //HIGH PRIORITY JOYSTICK
   if(ps2x.Button(PSB_R2))
  {
    if(ly<110)
    {
      int l=map(ly,110,0,0,255);
      Serial.println("FRL");
      //Serial.println(l);
    
      digitalWrite(FRD,HIGH);
      analogWrite(FR,l);
    }
  else if(ly>140)
  {
    int l=map(ly,140,255,0,255);
    Serial.println("FLL");
    //Serial.println(l);
    
    digitalWrite(FLD,HIGH);
    analogWrite(FL,l);
  }
  else if(lx<110)
  {
    int l=map(lx,110,0,0,255);
    Serial.println("BRL ");
    //Serial.println(l);
      
    digitalWrite(BRD,HIGH);
    analogWrite(BR,l);
    
  }
  else if(lx>140)
  {
    int l=map(lx,140,255,0,255);
    Serial.println("BLL");
    //Serial.println(l);
      
    digitalWrite(BLD,HIGH);
    analogWrite(BL,l);
  }
  else
  {
    digitalWrite(FR,LOW);
    digitalWrite(FL,LOW);
    digitalWrite(BL,LOW);
    digitalWrite(BR,LOW);
  }
  }
  else{
    digitalWrite(FR,LOW);
    digitalWrite(FL,LOW);
    digitalWrite(BL,LOW);
    digitalWrite(BR,LOW);}
     if(ps2x.ButtonPressed(GREEN_FRET))
      c=1;
            
     while(c==1)
      {
      digitalWrite(FRD,HIGH);
      analogWrite(FR,k);
      digitalWrite(BLD,HIGH);
      analogWrite(BL,k);
      delay(d);
      digitalWrite(FLD,HIGH);
      analogWrite(FL,k);
      digitalWrite(BRD,HIGH);
      analogWrite(BR,k);
      delay(d);
          if(ps2x.ButtonPressed(PSB_L1))
   {
    k+=25;
    if(k>=255)
    {
      k=25;
    }
   }
   if(ps2x.ButtonPressed(PSB_R1))
   {
    k-=25;
    if(k<=0)
    {
      k=25;
    }
   }
      if(ps2x.ButtonPressed(BLUE_FRET))
      {c=0;}
      }
       if(c==0)
       {
    digitalWrite(FR,LOW);
    digitalWrite(FL,LOW);
    digitalWrite(BL,LOW);
    digitalWrite(BR,LOW);
      }

  
}
