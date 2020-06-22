#define sensorPin  A14
void setup() {
  pinMode(sensorPin,INPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  int val=analogRead(sensorPin);
  Serial.println(val);
  delay(100);
  // put your main code here, to run repeatedly:

}
