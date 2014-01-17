#include <HTTPClient.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <HTTPClient01.h>
#include <stdio.h>
#include <Metro.h>
#include <Bridge.h>

char buffer[40];

//Metro sendingMetro = Metro(60000L);

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// assign an IP address for the controller:
byte ip[] = { 
  10,1,5,23 };
byte gateway[] = {
  10,1,5,1};	
byte subnet[] = { 
  255, 255, 255, 0 };

byte server[] = { 
  173,203,98,29 };

HTTPClient client('arduino.cc',server);

long lastConnectionTime = 0;        // last time you connected to the server, in milliseconds
boolean lastConnected = false;      // state of the connection last time through the main loop
const int postingInterval = 10000;  //delay between updates to Pachube.com

void setup() {

  Bridge.begin();
  Serial.begin(9600);

  delay(1000);
  Serial.println("ready");
  
}

void loop() {
  /*
  if(!client.connected()) {
    Serial.print("sending ");
    
    HTTPClient client("arduino.cc",server);
    
    FILE* result = client.getURI("/Reference/HomePage",NULL);
    
    int returnCode = client.getLastReturnCode();
    Serial.print("Status code: ");
    Serial.println(returnCode);
    
    if (result!=NULL) {
      client.closeStream(result);
    } 
    else {
      Serial.println("failed to connect");
    }
    if (returnCode==200) {
      Serial.println("data uploaded");
    } 
    else {
      Serial.print("ERROR: Server returned ");
      Serial.println(returnCode);
    }
  }*/
}




















