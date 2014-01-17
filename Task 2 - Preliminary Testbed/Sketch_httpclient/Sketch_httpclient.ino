// (c) Copyright 2010-2012 MCQN Ltd.
// Released under Apache License, version 2.0
//
// Simple example to show how to use the HttpClient library
// Get's the web page given at http://<kHostname><kPath> and
// outputs the content to the serial port

#include <SPI.h>
#include <HttpClient.h>
#include <Bridge.h>
#include <Ethernet.h>
#include <EthernetClient.h>

// This example downloads the URL "http://arduino.cc/"

// Name of the server we want to connect to
const char kHostname[] = "www.google.com";
// Path to download (this is the bit after the hostname in the URL
// that you want to download
const char kPath[] = "/";

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
  /*digitalWrite(13, HIGH);
  delay(1000);
  Ethernet.begin(mac,ip);
  digitalWrite(13, LOW);
  delay(1000);*/
  
  /*while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    digitalWrite(13, HIGH);
    delay(15000);
  }
  digitalWrite(13, LOW);*/  
}

void loop()
{
  int err =0;
 
  Serial.println("Starts the loop");
  
  EthernetClient c;
  HttpClient http(c);
  
  err = http.get(kHostname, kPath);
  /*IPAddress ipserver(10,1,67,4);
  const char path[] = "/FIN";
  
  const char* aServerName = "http://10.1.67.4";
  unsigned int aServerPort = 5555;
  const char* aURLPath = "/FIN";
  const char* aUserAgent = "sergio";
  
  err = http.post(aServerName,aServerPort,aURLPath,aUserAgent);
  Serial.println(err);*/
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = http.responseStatusCode();
    Serial.println(err);
    
    if (err >= 0)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      // Usually you'd check that the response code is 200 or a
      // similar "success" code (200-299) before carrying on,
      // but we'll print out whatever response we get

      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        int bodyLen = http.contentLength();
        Serial.print("Content length is: ");
        Serial.println(bodyLen);
        Serial.println();
        Serial.println("Body returned follows:");
      
        // Now we've got to the body, so we can print it out
        unsigned long timeoutStart = millis();
        char c;
        // Whilst we haven't timed out & haven't reached the end of the body
        while ( (http.connected() || http.available()) &&
               ((millis() - timeoutStart) < kNetworkTimeout) )
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
      }
      else
      {
        Serial.print("Failed to skip response headers: ");
        Serial.println(err);
      }
    }
    else
    {    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();

  // And just stop, now that we've tried a download
  while(1);
}
