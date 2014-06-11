#include <DHT.h>

#define DHTPIN 2 //data pin of the DHT sensor
#define DHTTYPE DHT22 //DHT 22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  Serial.print("The value of humidity is: ");
  Serial.println(humidity);
  
  Serial.print("The value of temperature is: ");
  Serial.println(temperature);
  
  delay(1000);

}
