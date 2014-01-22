#include <aJSON.h>


#include <avr/pgmspace.h>

const prog_char PROGMEM RETRIEVING_NAME[] ="Retrieving name\n";
const prog_char PROGMEM ERROR_RETRIEVING_NAME[] ="Error retrieving name\n";
const prog_char PROGMEM SUCCESSFULLY_RETRIEVED_NAME[] ="Successfully retrieved Name:";
const prog_char PROGMEM PARSING_OBJECT[] ="Parsing String\n";
const prog_char PROGMEM ERROR_PARSING_OBJECT[] ="Error parsing Object\n";
const prog_char PROGMEM SUCCESSFULLY_PARSED_OBJECT[] ="Successfully parsed Object\n";
const prog_char PROGMEM DELETING_OBJECT_STRING[] = "Deleting the object\n";
const prog_char PROGMEM FORMAT_FAILED_STRING[] = "Failed to create Format Object\n";
const prog_char PROGMEM OUTPUT_STRING_ERROR[] = "Error creating output String\n";
const prog_char PROGMEM RESULT_PRINTING_STRING[] = "Printing the result:\n";
const prog_char PROGMEM ADDING_FRAMERATE_STRING[] = "Adding frame rate to the format\n";
const prog_char PROGMEM ADDING_INTERLACE_STRING[] = "Adding interlace to the format\n";
const prog_char PROGMEM ADDING_HEIGHT_STRING[] = "Adding height to the format\n";
const prog_char PROGMEM ADDING_WIDTH_STRING[] = "Adding width to the format\n";
const prog_char PROGMEM ADDING_TYPE_STRING[] = "Adding type to the format\n";
const prog_char PROGMEM ADDING_FORMAT_STRING[] = "Adding format to the object\n";
const prog_char PROGMEM ADDING_LENGTH_STRING[] = "Adding length to the object\n";
const prog_char PROGMEM CREATING_FROMAT_STRING[] = "Creating format object\n";
const prog_char PROGMEM ADDING_NAME_STRING[] = "Adding name to the object\n";
const prog_char PROGMEM OBJECT_CREATION_FAILED_STRING[] = "Failed to create the object\n";
const prog_char PROGMEM OBJECT_CREATE_STRING[] = "Created a Object\n";
const prog_char PROGMEM HELLO_STRING[] = "********************\nTesting aJson\n*****************\n";

void setup() {
  Serial.begin(9600);
  freeMem("start");
}

void testJSON() {

  Serial.println("Empieza");
  
  aJsonObject* root = aJson.createObject();
  if (root != NULL) {
  } 
  else {
    return;
  }
  aJson.addItemToObject(root, "type", aJson.createItem(
  "FeatureCollection"));
  aJson.addStringToObject(root, "name", "Temperature Invented value1");
  aJson.addStringToObject(root, "timeStamp", "2014-01-20T10:31:06.655Z");
  aJsonObject* features = aJson.createArray();
  aJson.addItemToObject(root, "features", features);
  
  aJsonObject* featuresroot = aJson.createObject();
  aJson.addItemToArray(features,featuresroot);
  aJson.addItemToObject(featuresroot, "type", aJson.createItem(
  "Feature"));
  
  aJsonObject* tags = aJson.createArray();
  aJson.addItemToObject(featuresroot, "tags", tags);
  aJson.addItemToArray(tags,aJson.createItem("red"));
  aJson.addItemToArray(tags,aJson.createItem("tall"));
  aJson.addItemToArray(tags,aJson.createItem("cheap"));
  
  aJsonObject* geometry = aJson.createObject();
  aJson.addItemToObject(featuresroot, "geometry", geometry);
  aJson.addStringToObject(geometry, "type", "Point");
  aJsonObject* coordinates = aJson.createArray();
  aJson.addItemToObject(geometry, "coordinates", coordinates);
  aJson.addItemToArray(coordinates,aJson.createItem(2.167028));
  aJson.addItemToArray(coordinates,aJson.createItem(41.387547));

  aJsonObject* properties = aJson.createObject();
  aJson.addItemToObject(featuresroot, "properties", properties);
  aJson.addStringToObject(properties, "id", "1");
  aJson.addNumberToObject(properties, "name",1);
  /*aJson.addStringToObject(properties, "name", "SENSOR-TEMP-BCN-UPFPOBLENOU");
  aJson.addStringToObject(properties, "datasetId", "temperature");
  aJson.addStringToObject(properties, "datasetName", "temperature");
  aJson.addStringToObject(properties, "address", "Carrer de Tanger, Barcelona");
  aJson.addStringToObject(properties, "description", "Temperature sensor of UPF Poblenou");
  aJson.addStringToObject(properties, "timeStamp", "2014-01-20T10:31:06.655Z");
  aJson.addStringToObject(properties, "value", "21");
  aJson.addStringToObject(properties, "unit", "*C");
  aJson.addStringToObject(properties, "contentType", "video/ogg");
  aJson.addStringToObject(properties, "url", "http://download.blender.org/peach/trailer/trailer_1080p.ogg");
  aJson.addStringToObject(properties, "previewImage", "http://peach.blender.org/wp-content/uploads/poster_rodents_small.jpg");
  aJson.addStringToObject(properties, "size", "4");
  */
  
  
  freeMem("with object");
  char* string = aJson.print(root);
  if (string != NULL) {
    Serial.println(string);
  } 

  aJson.deleteItem(root);
  freeMem("after deletion");

  root = aJson.parse(string);
  free(string);
  freeMem("after printing");

  aJsonObject* name = aJson.getObjectItem(root, "name");
  aJson.deleteItem(root);
  freeMem("after deleting object");
}


void loop() {
  delay(1000);
  Serial.print("Llamando a testJSON...");
  testJSON();
  Serial.println("testJSON ha acabado");
  delay(5000);
}

// given a PROGMEM string, use Serial.print() to send it out
// this is needed to save precious memory
//htanks to todbot for this http://todbot.com/blog/category/programming/
void printProgStr(const prog_char* str) {
  char c;
  if (!str) {
    return;
  }
  while ((c = pgm_read_byte(str))) {
    Serial.print(c);
    str++;
  }
}

//Code to print out the free memory

struct __freelist {
  size_t sz;
  struct __freelist *nx;
};

extern char * const __brkval;
extern struct __freelist *__flp;

uint16_t freeMem(uint16_t *biggest)
{
  char *brkval;
  char *cp;
  unsigned freeSpace;
  struct __freelist *fp1, *fp2;

  brkval = __brkval;
  if (brkval == 0) {
    brkval = __malloc_heap_start;
  }
  cp = __malloc_heap_end;
  if (cp == 0) {
    cp = ((char *)AVR_STACK_POINTER_REG) - __malloc_margin;
  }
  if (cp <= brkval) return 0;

  freeSpace = cp - brkval;

  for (*biggest = 0, fp1 = __flp, fp2 = 0;
     fp1;
     fp2 = fp1, fp1 = fp1->nx) {
      if (fp1->sz > *biggest) *biggest = fp1->sz;
    freeSpace += fp1->sz;
  }

  return freeSpace;
}

uint16_t biggest;

void freeMem(char* message) {
  //Serial.print(message);
  //Serial.print(":\t");
  //Serial.println(freeMem(&biggest));
  freeMem(&biggest);
}



