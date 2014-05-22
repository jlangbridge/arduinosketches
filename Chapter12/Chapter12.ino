#include <SD.h>

const int chipSelect = 4;

int light;
int lightPin = 3;
unsigned int iteration = 1;


void setup()
{
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  // Chip Select pin needs to be set to output for the SD library
  pinMode(10, OUTPUT);
  
  // Attempt to initialize SD library
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  // Get a light level reading
  light = analogRead(lightPin);

  // Open the SD data file
  File dataFile = SD.open("light.txt", FILE_WRITE);

  // Has the file been opened?
  if (dataFile)
  {
      // Create a formatted string
      String dataString = "";
      dataString += String(iteration);
      dataString += ",";
      dataString += String(light);
      dataString += ",";
      
      // Print data to the serial port, and to the file
      Serial.println(dataString);
      dataFile.println(dataString);
      
      // Close the file
      dataFile.close();
  }
  
  // Increase the iteration number
  iteration++;
    
  // Sleep for one minute
  delay(60 * 1000);
}
