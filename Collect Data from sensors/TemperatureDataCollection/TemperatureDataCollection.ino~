// Code from
// http://www.matbra.com/en/2012/09/23/sensor-de-temperatura-com-arduino-e-lm35-arduino-lm35/ 
int analogPin = 0; 
int readValue = 0; 
float temperature = 0; 
float temperatureF = 0;

void setup() { 
  Serial.begin(9600); 
}

void loop() { 
  readValue = analogRead(analogPin);
  //Serial.println(readValue);
  temperature = (readValue * 0.0049); 
  temperature = temperature * 100; 
  temperatureF = (temperature * 1.8) + 32;
  Serial.print("Temperature: "); 
  Serial.print(temperature); 
  Serial.print("C ");
  Serial.print(temperatureF);
  Serial.println("F");
  delay(1000); 
}
