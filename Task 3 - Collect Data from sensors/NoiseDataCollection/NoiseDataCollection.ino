
#define THRESHOLD_VALUE 400//The threshold to turn the led on 400.00*5/1024 = 1.95v

int analogPin = 0;

void setup() {
  Serial.begin(9600); 

}

void loop() {
  int readValue = analogRead(analogPin);
  Serial.print("The value of the analogPing ");
  Serial.print(analogPin);
  Serial.print(" is: ");
  Serial.println(readValue);
  delay(1000);
}
