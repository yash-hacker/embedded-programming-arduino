#define trig A0
#define echo 9
void setup() {
  // put your setup code here, to run once:
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);

}
long duration=0;
int distance=0;
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  duration=pulseIn(echo,HIGH);
  distance=0.034*duration/2;
  Serial.println(distance);
  
  // put your main code here, to run repeatedly:

}
