#include <DHT.h>

#define DHTPIN 0 //data pin of the DHT sensor
#define DHTTYPE DHT22 //DHT 22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  float humidity = dht.readHumidity();
  Serial.print("The value of the analogPing ");
  Serial.print(DHTPIN);
  Serial.print(" is: ");
  Serial.println(humidity);
  delay(1000);

}
