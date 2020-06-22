int Xread;
int Xrest;
double Gx;
int sensorPin =0;


void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
digitalWrite(13,HIGH);
delay(1000);
Xrest=(analogRead(sensorPin));
Serial.print(Xrest);
digitalWrite(13,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
Xread=analogRead(sensorPin)-Xrest;
Gx=Xread/67.540;
Serial.print("Gyroscope_x= ");
Serial.println(Gx);
delay (1000);
}
