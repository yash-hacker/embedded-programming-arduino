#include <Servo.h>
Servo myservo;
void setup() {
pinMode(A0,INPUT);       // switch is connected
myservo.attach(9);
Serial.begin(9600);
Serial.println("switch");
myservo.write(0);
while(!digitalRead(A0))
{
  Serial.println(digitalRead(A0));
  }
myservo.write(70);
Serial.println("signal");
}
void loop() { 

}
