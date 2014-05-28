#include <DHT.h>
#include <Process.h>
#include <FileIO.h>


#define DHTPIN 2 // The DHT sensor has to be in the digital pin 2 
#define DHTTYPE DHT11 //DHT 11
String ARDUINO_YUN_UNIQUE_ID = "2";

DHT dht(DHTPIN, DHTTYPE);

int TEMPERATURE_SENSOR = 1; // The temperature sensor has to be in the analog pin 1
int LIGHT_SENSOR = 2; // The light sensor has to be in the analog pin 2
int NOISE_SENSOR = 0; // The noise sensor has to be in the analog pin 0
int GAS_SENSOR = 3; // The gas sensor has to be in the analog pin 3

void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial
  FileSystem.begin();  // Initialize the FileSystem
}

// This function return a string with the time stamp
String getTimeStamp() {
  String res;
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
      res += c;
  }

  return res;
}

String readLightSensor(){

    int sensorvalue = analogRead(LIGHT_SENSOR);

//  Resistance in the circuit of sensor 0 (KOhms)
    float Res = 10.0;              
    
//  The value of the light sensor can be from 0(0V) to 1024(5V)
//  For example, if the sensorvalue is 25, the Vout = (5/1024)*25
    float Vout = sensorvalue * 0.0048828;
    
//  This formula is explained in the final report
    float Vmax = 5.0;
    int lux0 = (500*Vmax/Vout - 500)/Res;  // calculate the Luxs
  
  return String(lux0);
}      

String readGasSensor(){
  int gas = analogRead(GAS_SENSOR);
  return String(gas);
}              

String readHumiditySensor(){

//  This function call the library function to calculate the humidity value
    float humidity = dht.readHumidity();
    return String(humidity);
}

String readTemperatureSensor(){

//  This convert the the sensorvalue in a temperature value in celsius
    int sensorvalue = analogRead(TEMPERATURE_SENSOR);
    float Vmax = 5.0;
    int temperatureC = (Vmax * sensorvalue * 100.0)/1024;
  
  return String(temperatureC);
}

String readNoiseSensor(){
  
//  This function measures the noise value, from 0 to 1024.
    float sensorvalue = 0.0;
    int rounds = 10;
//  It measures the noise 10 times with a delay of 1 second, to avoid false measures
    for(int i=0; i<rounds; i++){
      sensorvalue = sensorvalue + analogRead(NOISE_SENSOR);
      delay(1000);
    }
    sensorvalue = sensorvalue/rounds;
    return String(sensorvalue);
}

void readSensors(String *temperature, String *humidity, String *noise, String *ligth, String *gas){

//  It calls all the functions to read the values of the sensors. 
    *temperature = readTemperatureSensor();
    //Serial.println("Ha leido la temperatura");
    *humidity = readHumiditySensor();
    //Serial.println("Ha leido la humedad");
    *noise = readNoiseSensor();
    //Serial.println("Ha leido el ruido");
    *ligth = readLightSensor();
    //Serial.println("Ha leido la luz");
    *gas = readGasSensor();
    //Serial.println("Ha leido el gas");
}

int readFile(String *temperature, String *humidity, String *noise, String *ligth, String *gas){

//  If the logData file does not exist, it creates one.    
    if( !FileSystem.exists("/mnt/sda1/arduino/www/logData") ){
      File dataFileWrite = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_WRITE);
      dataFileWrite.close();
    }
    
//  It opens the logData file to read it.
    File dataFileRead = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_READ);
    
    String output = "";
    int id = 1;
    String result = "";
    
    int c = 0;

    if( !dataFileRead.available() ){
      //Serial.println("empty file");
//    If the logData file is empty, it starts with an id equal to 1, and creates a String which contains the id and the values from the sensors.
      result = String(id) + " " + *temperature + " " + *humidity + " " + *noise + " " + *ligth + " " + *gas + " " + getTimeStamp();
    }else{
      //Serial.println("not empty file");
//    If the logData file is not empty, it stores all the file in the output variable.
      while(dataFileRead.available()){
          output += (char)dataFileRead.read(); 
      }

//    This peace of code is to obtein the last write line.
      String lastline = "";
      for( int i=output.length()-2; i>=0; --i ){
        
        if( output[i] == '\n' )
          break;
        lastline += output[i];      
      }
      
//    This is to get the last ID.
      String sid = "";
      for( int i=lastline.length()-1; i>=0; --i ){
        
        if( lastline[i] == ' ' )
          break;
        sid += lastline[i];      
      }
      id = atoi(sid.c_str());
      id += 1;
//    This is the same string as in the first if, but with a new ID
      result = String(id) + " " + *temperature + " " + *humidity + " " + *noise + " " + *ligth + " " + *gas + " " + getTimeStamp();
    }
    
    dataFileRead.close();

//  Now it writes down the new entrance in the logData file.
    File dataFileAppend = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_APPEND);

//  If the file is available, write to it:
    if (dataFileAppend) {
      dataFileAppend.print(result);
      dataFileAppend.print("\n");
      dataFileAppend.close();
      //Serial.println(result);
    }  
//  If the file isn not open, it will show an error:
    else {
      Serial.println("error opening logData");
    }
    
    return id;
}

void executePythonScript(int id,String *temperature, String *humidity, String *noise, String *ligth, String *gas){

//  It calls the python script like a command shell: python main.py id temperature light noise humidity
    Process myscript;
    String a = "python /mnt/sda1/arduino/www/main.py " + ARDUINO_YUN_UNIQUE_ID + "." + String(id) + " " + *temperature + " " + *ligth + " " + *noise + " " + *humidity + " " + *gas;
    Serial.println("Llamada a main.py: ");
    Serial.println("\t" + a );
    myscript.runShellCommand(a); 
    while (myscript.running());
    
    String output = "";

//  Read the output of the script
    while (myscript.available()) {
      output += (char)myscript.read();   
    }
//  Remove the blank spaces at the beginning and the ending of the string
    output.trim();
    Serial.println(output);
  
}

void loop() {
  
    String temperature, humidity, noise, ligth, gas;
    
//  The next function will call all the other functions to read the value of the sensors attached to the arduino.
    readSensors(&temperature, &humidity, &noise, &ligth, &gas);
    
//  This function reads the logData file stored in the SDCard, and write a new line with the next unique ID.
    int id = readFile(&temperature, &humidity, &noise, &ligth, &gas);
    
//  This function calls the python script (main.py) stored in the SDCard with the ID, and the values of the sensors.
    executePythonScript(id,&temperature, &humidity, &noise, &ligth, &gas); 

//  This delay plus the delay added at the noise read plus the processing delay would make an aproximate total delay of 1 minute.
    delay(48000);
}


















