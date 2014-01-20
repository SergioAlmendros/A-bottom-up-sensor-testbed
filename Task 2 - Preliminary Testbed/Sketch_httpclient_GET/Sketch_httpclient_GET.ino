// (c) Copyright 2010-2012 MCQN Ltd.
// Released under Apache License, version 2.0
//
// Simple example to show how to use the HttpClient library
// Get's the web page given at http://<kHostname><kPath> and
// outputs the content to the serial port

#include <SPI.h>
#include <HttpClient.h>
#include <Bridge.h>
#include <YunClient.h>


byte mac[] = { 0x90, 0xA2, 0xDA, 0xF8, 0x0A, 0x13 };
byte ip[] = { 10, 1, 67, 18 };

// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

void setup()
{
  // initialize serial communications at 9600 bps:
  Bridge.begin();
  Serial.begin(9600);
  //Ethernet.begin(mac, ip); 

}

void loop()
{
  int responseCode = 0;
 
  Serial.println("Starts the loop");
  
  int myVal = 3;
  int postDataLen = 0;
  
  postDataLen += sizeof("value=");
  postDataLen += sizeof(myVal);
  
  //EthernetClient c;
  YunClient c;
  //c.connect("www.google.com",80);
  HttpClient http(c);
  
  http.beginRequest();
  //http.get("http://10.1.67.4:5555", "/someform");
  //http.get("http://192.168.2.112:5555", "/someform");
  http.get("www.upf.edu", "/"); 
  http.endRequest();
  
  
  responseCode = http.responseStatusCode();

  Serial.println(responseCode);
  
  if ((responseCode >= 200) && (responseCode < 300)) {
    // Successful response
    if (http.skipResponseHeaders() >= 0) {
      // We're into reading the body of the response now...
      int bodyLen = http.contentLength();
      Serial.print("Content length is: ");
      Serial.println(bodyLen);
      Serial.println();
      Serial.println("Body returned follows:");
      
      // Now we've got to the body, so we can print it out
      unsigned long timeoutStart = millis();
      char c;
      // Whilst we haven't timed out & haven't reached the end of the body
      while ( (http.connected() || http.available()) && ((millis() - timeoutStart) < kNetworkTimeout) )
      {
        if (http.available())
        {
          c = http.read();
          // Print out this character
          Serial.print(c);
           
          bodyLen--;
          // We read something, reset the timeout counter
          timeoutStart = millis();
        }
        else
        {
          // We haven't got any data, so let's pause to allow some to
          // arrive
          delay(kNetworkDelay);
        }
      }
     
    }else
    {
      Serial.println("Error skip response Headers");
    }
  }
  
}














