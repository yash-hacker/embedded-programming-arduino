#define SWITCH 9
void setup() {
  // put your setup code here, to run once:
pinMode(SWITCH,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x=digitalRead(SWITCH);
if(x==1)
{
  Serial.println("switch ON");
}
else
Serial.println("switch OFF");
}
