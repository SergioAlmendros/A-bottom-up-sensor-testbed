/*
  Running shell commands using Process class.

 This sketch demonstrate how to run linux shell commands
 using an Arduino Yún. It runs the wifiCheck script on the linino side
 of the Yun, then uses grep to get just the signal strength line.
 Then it uses parseInt() to read the wifi signal strength as an integer,
 and finally uses that number to fade an LED using analogWrite().

 The circuit:
 * Arduino Yun with LED connected to pin 9

 created 12 Jun 2013
 by Cristian Maglie
 modified 25 June 2013
 by Tom Igoe

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/ShellCommands

 */

#include <Process.h>

void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial

  // Wait until a Serial Monitor is connected.
  while (!Serial);
}

void loop() {
  //Process p;
  //p.runShellCommand("python /mnt/sda1/arduino/www/hello.py");
  //while (p.running());
  
  Process myscript;
  //myscript.begin("/mnt/sda1/arduino/www/hello.py");
  //myscript.run();
  myscript.runShellCommand("python /mnt/sda1/arduino/www/hello.py");
  while (myscript.running());
  
  String output = "";

  // read the output of the script
  while (myscript.available()) {
    output += (char)myscript.read();
  }
  // remove the blank spaces at the beginning and the ending of the string
  output.trim();
  Serial.println(output);
  //Serial.flush();
  
  delay(5000);  // wait 5 seconds before you do it again
}



