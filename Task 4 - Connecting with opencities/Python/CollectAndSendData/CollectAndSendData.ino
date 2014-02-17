#include <Process.h>
#include <FileIO.h>
#include <DHT.h>

#define DHTPIN 2 //data pin of the DHT sensor
#define DHTTYPE DHT22 //DHT 22
String ARDUINO_YUN_UNIQUE_ID = "1";

DHT dht(DHTPIN, DHTTYPE);

int TEMPERATURE_SENSOR = 1;
int LIGHT_SENSOR = 2;
int NOISE_SENSOR = 0;

void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial
  FileSystem.begin();  // Initialize the FileSystem
}

String readLightSensor(int sensorvalue){
  float Res0=10.0;              // Resistance in the circuit of sensor 0 (KOhms)
  float Vout0 = sensorvalue * 0.0048828125;      // calculate the voltage
  int lux0=500/(Res0*((5-Vout0)/Vout0));  // calculate the Lux
  
  return String(lux0);
}                    

String readHumiditySensor(){
  float humidity = dht.readHumidity();
  return String(humidity);
}

String readTemperatureSensor(int sensorvalue){
  int temperature = (sensorvalue * 0.0049); 
  temperature = temperature * 100; 
  int temperatureF = (temperature * 1.8) + 32;
  
  return String(temperatureF);
}

String readNoiseSensor(){
  //Hay que hacer pruebas para saber que valor es silencio, y que valor es mucho ruido
  float sensorvalue = 0.0;
  int rounds = 10;
  for(int i=0; i<rounds; i++){
    sensorvalue = sensorvalue + analogRead(NOISE_SENSOR);
    delay(1000);
  }
  sensorvalue = sensorvalue/rounds;
  return String(sensorvalue);
}

void readSensors(String *temperature, String *humidity, String *noise, String *ligth){  
  *temperature = readTemperatureSensor(analogRead(TEMPERATURE_SENSOR));
  *humidity = readHumiditySensor();
  *noise = readNoiseSensor();
  *ligth = readLightSensor(analogRead(LIGHT_SENSOR));
}

int readFile(String *temperature, String *humidity, String *noise, String *ligth){
  
  File dataFileRead = FileSystem.open("/mnt/sda1/arduino/www/logData", FILE_READ);
  
  String output = "";
  int id = 1;
  String result = "";
  
  int c = 0;

  if( !dataFileRead.available() ){
    //Serial.println("archivo vacio");
    result = String(id) + " " + *temperature + " " + *humidity + " " + *noise + " " + *ligth;
  }else{
    //Serial.println("archivo lleno");
    
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
  String a = "python /mnt/sda1/arduino/www/main.py " + ARDUINO_YUN_UNIQUE_ID + "." + String(id) + " " + *temperature + " " + *ligth + " " + *noise + " " + *humidity;
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

  delay(48000); //This delay plus the delay added at the noise read plus the processing delay would make a total delay of 1 minute.
}


















