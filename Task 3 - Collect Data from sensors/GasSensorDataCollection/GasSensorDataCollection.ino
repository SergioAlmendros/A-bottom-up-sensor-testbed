int gasSensorValue;

void setup(){
  Serial.begin(9600);
}


void loop(){
  //The gasSensorValue goes from 0 to 1024, 0: No gas.
  gasSensorValue = analogRead(0);
  Serial.println(gasSensorValue, DEC);
  delay(100);   
}
