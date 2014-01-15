
#include <Bridge.h>
#include <YunClient.h>

void setup() {
  Serial.begin(9600);

  // Bridge startup
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  YunClient client;
  client.connect("192.168.2.112",5555);
  //client.write('F');
  //client.write('I');
  //client.write('N');
  client.println("FIN");
  client.stop();
}
