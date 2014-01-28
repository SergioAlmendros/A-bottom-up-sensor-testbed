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
#include <FileIO.h>

void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial
  FileSystem.begin();
  
  // Wait until a Serial Monitor is connected.
  while (!Serial);
}

void loop() {
  
  String dataString;
  //dataString += getTimeStamp();
  //dataString += " = ";
  
  //FALTA LEER LOS SENSORES
  dataString += "-5-6-7-8";
  
  File dataFile = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_APPEND);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(dataString);
    dataFile.print("\n");
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
  /*
  Process myscript;
  myscript.runShellCommand("python /mnt/sda1/arduino/www/main.py 2 3 4 5"); 
  while (myscript.running());
  
  String output = "";

  // read the output of the script
  while (myscript.available()) {
    output += (char)myscript.read();   
  }
  // remove the blank spaces at the beginning and the ending of the string
  output.trim();
  Serial.println(output);*/
  //Serial.flush();
  
  delay(5000);  // wait 5 seconds before you do it again
}

String getTimeStamp() {
  String result;
  Process time;
  // date is a command line utility to get the date and the time 
  // in different formats depending on the additional parameter 
  time.begin("date");
  time.addParameter("+%D-%T");  // parameters: D for the complete date mm/dd/yy
                                //             T for the time hh:mm:ss    
  time.run();  // run the command

  // read the output of the command
  while(time.available()>0) {
    char c = time.read();
    if(c != '\n')
      result += c;
  }

  return result;
}



