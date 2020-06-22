#include <Servo.h>
Servo myservo;
int pos=0;
int count= 0;
void setup() {       // switch is connected
myservo.attach(35);
Serial.begin(9600);
pos= myservo.read();
Serial.println(pos);
myservo.write(180);
while(digitalRead(A0)==0)
{
  Serial.println("no signal");
}
 myservo.write(65);
}

void loop() {
  

}
