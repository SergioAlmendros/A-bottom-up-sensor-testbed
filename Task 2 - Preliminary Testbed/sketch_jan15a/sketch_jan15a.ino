#include <Bridge.h>
#include <HttpClient.h>

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Serial.begin(9600);
}

void loop() {
  HttpClient client;
  client.get("http://192.168.2.112:5555/FIN");
    //IP of the PC where is the server, in my case, 192.168.2.112.
    //Port where the server is listening, in my case, 5555.

  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.flush();

  delay(5000);
}
