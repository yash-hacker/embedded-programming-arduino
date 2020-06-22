/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);
//   avoid using pins with LEDs attached
int t=0;
int i=0;


void setup() {
  pinMode(40,OUTPUT);
  pinMode(42,OUTPUT);
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
 digitalWrite(40,0);
digitalWrite(42,HIGH);
}

double oldPosition  = -999;

void loop() {
  
  double newPosition = myEnc.read();

    if(newPosition != oldPosition)
  
    {  t=millis();
      int diff= (t-i);
      int rpm=(60000*(newPosition-oldPosition))/(diff*384)*-1;
     Serial.println(rpm);
     i=t;
     oldPosition = newPosition;
    }
    
  }
