const byte analogPin = 0;         // analog output of front_LSA08  
const byte junctionPulse_1 = 4;    // junction pulse of front_LSA08 

int read_value,position_1;
void setup() {
  // put your setup code here, to run once:
pinMode(junctionPulse_1,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
read_value=analogRead(analogPin);
position_1=((float)read_value/921)*70;
Serial.println(position_1);
}
