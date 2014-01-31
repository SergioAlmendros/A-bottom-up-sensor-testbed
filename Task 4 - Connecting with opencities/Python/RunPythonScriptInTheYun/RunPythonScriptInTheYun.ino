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
  int id = 1;
  String result = "";
  
  int c = 0;

  if( !dataFileRead.available() ){
    Serial.println("archivo vacio");
    result = String(id) + " " + *temperature + " " + *humidity + " " + *noise + " " + *ligth;
  }else{
    Serial.println("archivo lleno");
    
    while(dataFileRead.available()){
        output += (char)dataFileRead.read(); 
    }

    String lastline = "";
   
    for( int i=output.length()-2; i>=0; --i ){
      
      if( output[i] == '\n' )
        break;
      lastline += output[i];      
    }
        
    // remove the blank spaces at the beginning and the ending of the string
    output.trim();
    
    //Coger el numero hasta que haya un espacio
    String sid = "";
    for( int i=lastline.length()-1; i>=0; --i ){
      
      if( lastline[i] == ' ' )
        break;
      sid += lastline[i];      
    }
    id = atoi(sid.c_str());
    id += 1;
    result = String(id) + " " + *temperature + " " + *humidity + " " + *noise + " " + *ligth;
  }

  //Serial.println(result);
  
  dataFileRead.close();

  File dataFileAppend = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_APPEND);

  // if the file is available, write to it:
  if (dataFileAppend) {
    dataFileAppend.print(result);
    dataFileAppend.print("\n");
    dataFileAppend.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  
  return id;
}

void executePythonScritp(int id,String *temperature, String *humidity, String *noise, String *ligth){
  
  Process myscript;
  String a = "python /mnt/sda1/arduino/www/main.py " + String(id) + " " + *temperature + " " + *ligth + " " + *noise + " " + *humidity;
  Serial.println("Llamada a main.py: ");
  Serial.println("\t" + a );
  myscript.runShellCommand(a); 
  while (myscript.running());
  
  String output = "";

  // read the output of the script
  while (myscript.available()) {
    output += (char)myscript.read();   
  }
  // remove the blank spaces at the beginning and the ending of the string
  output.trim();
  Serial.println(output);
  
}

void loop() {
  
  String temperature, humidity, noise, ligth;
  readSensors(&temperature, &humidity, &noise, &ligth);
  int id = readFile(&temperature, &humidity, &noise, &ligth);
  executePythonScritp(id,&temperature, &humidity, &noise, &ligth); 

  //delay(60000);  // wait 60 seconds before you do it again
  delay(5000);
}


















