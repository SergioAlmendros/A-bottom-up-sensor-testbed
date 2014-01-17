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
  int responseCode =0;
 
  Serial.println("Starts the loop");
  
  //EthernetClient c;
  YunClient c;
  HttpClient http(c);
  
  http.beginRequest();
  http.get("www.upf.edu", "/");
  http.endRequest();
  
  responseCode = http.responseStatusCode();
  
  /*Serial.print("Status code: ");
  if(responseCode == -3 ) Serial.print("Timed out");*/
  Serial.println(responseCode);
  
  if ((responseCode >= 200) && (responseCode < 300)) {
         // Successful response
         if (http.skipResponseHeaders() >= 0) {
             // We're into reading the body of the response now...
             int sizeOfResponse = http.contentLength();
             
                 if (http.available()) {
                     char c = http.read();
                     Serial.println(c);
                 }
             
         }else
         {
           Serial.println("Error skip response Headers");
         }
  }
  
  
  
}














