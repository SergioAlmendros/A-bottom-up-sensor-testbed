#include <DHT.h>
#include <Process.h>
#include <FileIO.h>


#define DHTPIN 2 // The DHT sensor has to be in the digital pin 2 
#define DHTTYPE DHT22 //DHT 22
String ARDUINO_YUN_UNIQUE_ID = "3"; //ID 1: Ferran, ID 2: Sergio, ID 3: Uni

DHT dht(DHTPIN, DHTTYPE);

int TEMPERATURE_SENSOR = 1; // The temperature sensor has to be in the analog pin 1
int LIGHT_SENSOR = 2; // The light sensor has to be in the analog pin 2
int NOISE_SENSOR = 0; // The noise sensor has to be in the analog pin 0
int GAS_SENSOR = 3; // The gas sensor has to be in the analog pin 3

int ID;

//Variables for setTimestamp function
  String Stime;
  Process time;
  char c;

//Variables for readLightSensor function
  int LightSensorValue;
  String SLightSensor;

//Variables for readGasSensor function
  String SGasSensor;

//Variables for readHumiditySensor function
  String SHumiditySensor;

//Variables for readTemperatureSensor function
  String STemperatureSensor;
  
//Variables for readNoiseSensor function  
  float NoiseSensorValue;
  String SNoiseSensor;
  
//Variables for readFile function
  String output;
  String result;
  String lastline;
  String sid;

//Variables for executePythonScript function  
  Process myscript;
  String a;
  
void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial
  FileSystem.begin();  // Initialize the FileSystem
}

// This function return a string with the time stamp
void setTimeStamp() {
  //String res;
  //Process time;
  // date is a command line utility to get the date and the time 
  // in different formats depending on the additional parameter 
  time.begin("date");
  time.addParameter("+%D-%T");  // parameters: D for the complete date mm/dd/yy
                                //             T for the time hh:mm:ss    
  time.run();  // run the command
  Stime = "";
  // read the output of the command
  while(time.available()>0) {
    c = time.read();
    if(c != '\n')
      Stime += c;
  }

  //return res;
}

void readLightSensor(){

//  Resistance in the circuit of sensor 0 (KOhms)            
//  The value of the light sensor can be from 0(0V) to 1024(5V)
//  For example, if the sensorvalue is 25, the Vout = (5/1024)*25
//  This formula is explained in the final report
    //LightSensorValue = (500*5.0/(analogRead(LIGHT_SENSOR) * 0.0048828) - 500)/10.0;  // calculate the Luxs
    SLightSensor = String((500*5.0/(analogRead(LIGHT_SENSOR) * 0.0048828) - 500)/10.0);
}      

void readGasSensor(){
  
  SGasSensor = String(analogRead(GAS_SENSOR));
}              

void readHumiditySensor(){

//  This function call the library function to calculate the humidity value
    SHumiditySensor = String(dht.readHumidity());
}

void readTemperatureSensor(){

//  This convert the the sensorvalue in a temperature value in celsius
    //int temperatureC = (5.0 * analogRead(TEMPERATURE_SENSOR) * 100.0)/1024;
  STemperatureSensor = String((5.0 * analogRead(TEMPERATURE_SENSOR) * 100.0)/1024);
}

void readNoiseSensor(){
  
//  This function measures the noise value, from 0 to 1024.
    NoiseSensorValue = 0.0;
//  It measures the noise 10 times with a delay of 1 second, to avoid false measures
    for(int i=0; i<10; i++){
      NoiseSensorValue = NoiseSensorValue + analogRead(NOISE_SENSOR);
      delay(1000);
    }
    SNoiseSensor = String(NoiseSensorValue/10);
}

void readSensors(){

//  It calls all the functions to read the values of the sensors. 
    readTemperatureSensor();
    readHumiditySensor();
    readNoiseSensor();
    readLightSensor();
    readGasSensor();
}

void readFile(){

  //  If the logData file does not exist, it creates one.    
  if( !FileSystem.exists("/mnt/sda1/arduino/www/logData") || !FileSystem.exists("/mnt/sda1/arduino/www/logID") ){
    
    File dataFileWrite = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_WRITE);
    
    ID = 1;
    result = String(ID) + " " + STemperatureSensor + " " + SHumiditySensor + " " + SNoiseSensor + " " + SLightSensor + " " + SGasSensor + " " + Stime;
    dataFileWrite.print(result);
    dataFileWrite.print("\n");
    dataFileWrite.close();
    ID++;
    
    File dataFileWriteID = FileSystem.open("/mnt/sda1/arduino/www/logID", FILE_WRITE);
    dataFileWriteID.print(String(ID));
    dataFileWriteID.print("\n");
    dataFileWriteID.close();
  }else{
    
    File dataFileReadID = FileSystem.open("/mnt/sda1/arduino/www/logID", FILE_READ);
    output = "";
    while(dataFileReadID.available()){
        output += (char)dataFileReadID.read();
    }
    ID = atoi(output.c_str());
    dataFileReadID.close();
    
    
    File dataFileAppend = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_APPEND);
    result = String(ID) + " " + STemperatureSensor + " " + SHumiditySensor + " " + SNoiseSensor + " " + SLightSensor + " " + SGasSensor + " " + Stime;
    dataFileAppend.print(result);
    dataFileAppend.print("\n");
    dataFileAppend.close();

    ID++;
    File dataFileWriteIDN = FileSystem.open("/mnt/sda1/arduino/www/logID", FILE_WRITE);
    dataFileWriteIDN.print(String(ID));
    dataFileWriteIDN.print("\n");
    dataFileWriteIDN.close();
   
  }
  Serial.println(result);
}

void executePythonScript(){

//  It calls the python script like a command shell: python main.py id temperature light noise humidity
    a = "python /mnt/sda1/arduino/www/main.py " + ARDUINO_YUN_UNIQUE_ID + "." + String(ID) + " " + STemperatureSensor + " " + SHumiditySensor + " " + SNoiseSensor + " " + SLightSensor + " " + SGasSensor;
    //Serial.println("Llamada a main.py: ");
    //Serial.println("\t" + a );
    myscript.runShellCommand(a); 
    while (myscript.running());
    
    //output = "";

//  Read the output of the script
    //while (myscript.available()) {
      //output += (char)myscript.read();   
    //}
//  Remove the blank spaces at the beginning and the ending of the string
    //output.trim();
    //Serial.println(output);
  
}

void loop() {
  
    setTimeStamp();
    //Serial.println("ReadSensors");
//  The next function will call all the other functions to read the value of the sensors attached to the arduino.
    readSensors();
    
    //Serial.println("ReadFile\n");
//  Serial.println("Leyendo del archivo");
//  This function reads the logData file stored in the SDCard, and write a new line with the next unique ID.
    readFile();
    
//  Serial.println("Ejecutando el script de python");
//  This function calls the python script (main.py) stored in the SDCard with the ID, and the values of the sensors.
    executePythonScript(); 

//  This delay plus the delay added at the noise read plus the processing delay would make an aproximate total delay of 1 minute.
    delay(48000);
    //delay(1000);
}


















