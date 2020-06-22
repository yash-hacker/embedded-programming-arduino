void setup() {
  // put your setup code here, to run once:

pinMode(A0,INPUT); 
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int n=(digitalRead(A0));
  Serial.println(n);
  if(n==0)
  {
    Serial.println("switch ON");
    
  }
  else
  Serial.println("switch OFF");
}
