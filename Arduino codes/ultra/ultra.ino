#define trig2 11
#define echo2 12
void setup() {
pinMode(trig2,OUTPUT);
pinMode(echo2,INPUT);
Serial.begin(9600);
}

void loop() {
digitalWrite(trig2,LOW);
    delayMicroseconds(2);
    digitalWrite(trig2,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2,LOW);
   unsigned long duration2=pulseIn(echo2,HIGH);
   unsigned long distance2=0.034*(duration2/2);
    Serial.println(distance2);

}
