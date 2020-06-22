/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
long i=0;
long t=0;
#define pwm 40
#define dir 42
#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);

//   avoid using pins with LEDs attached

void setup() {
  //pinMode(pwm,OUTPUT);
  //pinMode(dir,OUTPUT);
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  //digitalWrite(pwm,0);
  //digitalWrite(dir,0);
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  
  if (newPosition != oldPosition) {
    long t=millis();
    long diff=(t-i);
    float rpm=(((newPosition-oldPosition)*60000));
    Serial.println(rpm);
    long i=t;
    oldPosition = newPosition;
    
  }
}
