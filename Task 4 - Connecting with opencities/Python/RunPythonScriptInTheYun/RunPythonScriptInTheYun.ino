#include <Process.h>
#include <FileIO.h>


void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial
  FileSystem.begin();  // Initialize the FileSystem
}

void readSensors(String *temperature, String *humidity, String *noise, String *ligth){  
  *temperature = "5.14";
  *humidity = "115";
  *noise = "26";
  *ligth = "12";
}

int readFile(String *temperature, String *humidity, String *noise, String *ligth){
  
  File dataFileRead = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_READ);
  
  String output = "";
  while(dataFileRead.available()){
    output += (char)dataFileRead.read();   
  }
  // remove the blank spaces at the beginning and the ending of the string
  output.trim();
  //Serial.println(output);
  int id = 1;
  String result = "";
  if( output = "" ){
    Serial.println("archivo vacio");
    result = str(id) + " " + *temperature + " " + *humidity + " " + *noise + " " + *ligth;
  }else{
    Serial.println("archivo lleno");
    result = " " + *temperature + " " + *humidity + " " + *noise + " " + *ligth;
  }
  
  dataFileRead.close();
  
  /*
  
  File dataFileAppend = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_APPEND);

  // if the file is available, write to it:
  if (dataFileAppend) {
    dataFileAppend.print(dataSensors);
    dataFileAppend.print("\n");
    dataFileAppend.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } */
  
}

void executePythonScritp(String dataSensors,int id){
  
  Process myscript;
  
  /*
  char *p = dataSensors;
  char *str;
  while ((str = strtok_r(p, "-", &p)) != NULL)
    Serial.println(str);

  myscript.runShellCommand("python /mnt/sda1/arduino/www/main.py " + dataSensors); 
  while (myscript.running());
  
  String output = "";

  // read the output of the script
  while (myscript.available()) {
    output += (char)myscript.read();   
  }
  // remove the blank spaces at the beginning and the ending of the string
  output.trim();
  Serial.println(output);*/
  
}

void loop() {
  
  String temperature, humidity, noise, ligth;
  readSensors(&temperature, &humidity, &noise, &ligth);
  readFile(&temperature, &humidity, &noise, &ligth);
  
  
  //int id = readFile(dataSensors);
  //executePythonScritp(dataSensors,id); 

  //delay(60000);  // wait 60 seconds before you do it again
  delay(5000);
}


















