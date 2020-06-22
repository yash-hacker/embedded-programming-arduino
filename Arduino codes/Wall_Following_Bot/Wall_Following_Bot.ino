#define pwm1 7
#define dir1 6
#define pwm2 9
#define dir2 8
#define trig1 10
#define trig2 5
#define echo1 3
#define echo2 4 
void setup() {
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(trig1,OUTPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}
long duration1=0;
long duration2=0;
int distance1=0;
int distance2=0;
int motor_speed1=200;
int motor_speed2=200;
int slow1=100;
int slow2=100;
int diff=0;
void loop() {
  sensor1(trig1,echo1);
  distance1=0.034*duration1/2;
  sensor2(trig2,echo2);
  distance2=0.034*duration2/2;
  diff = distance1 - distance2;
  Serial.println(distance1);
  Serial.println(distance2);
  Serial.println(diff);
  if(diff>4)
  {
    analogWrite(pwm1,motor_speed1);
    analogWrite(pwm2,motor_speed2);
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
    Serial.println("MOVE RIGHT");
  }
  if(diff<-3)
  {
    analogWrite(pwm1,motor_speed1);
    analogWrite(pwm2,motor_speed2);
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    Serial.println("MOVE LEFT");
  }
  /*if(distance2>=20 && distance2<=15)
  {
    analogWrite(pwm1,motor_speed1);
    analogWrite(pwm2,motor_speed2);
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
  }
  if(distance2<15)
  {
    analogWrite(pwm1,motor_speed1);
    analogWrite(pwm2,motor_speed2);
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
  }*/
 if(diff<=4 && diff>=-3)
  {
    analogWrite(pwm1,motor_speed1);
    analogWrite(pwm2,motor_speed2);
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,LOW);
    Serial.println("STRAIGHT");
  }
 
  delay(100);
}
void sensor1(int trig, int echo)
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  duration1=pulseIn(echo,HIGH);
}
void sensor2(int trig, int echo)
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  duration2=pulseIn(echo,HIGH);
}
