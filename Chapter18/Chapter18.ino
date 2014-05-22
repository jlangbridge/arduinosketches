#include <SD.h>
#include <SPI.h>
#include <Audio.h>

const int buttonPin = 7; // The pushbutton pin
const int sensorPin = A0; // The analog input pin

void setup()
{
  // Debug output at 9600 baud
  Serial.begin(9600);

  // Set up SD-card. Check your board for the pin to use
  if (!SD.begin(4))
  {
    Serial.println("SD initialization failed!");
    return;
  }

  // Configure high-speed SPI transfers
  SPI.setClockDivider(4);

  // 44100Khz mono files, 100 mSec of prebuffering.
  Audio.begin(44100, 100);
  
  // Configure pins
  pinMode(buttonPin, INPUT);
  pinMode(sensorPin, INPUT);
}

void loop()
{
  // Wait for a button to be pressed
  
  if (digitalRead(buttonPin))
  {
    // read the value from the sensor:
    int sensorValue = analogRead(sensorPin);
  
    Serial.print("Sensor reading: ");
    Serial.print(sensorValue, DEC);
  
    // Convert the temperature
    int tempC = ( 3.3 * analogRead(sensorPin) * 100.0) / 1024.0; // 3.3V on the due
    Serial.print(" Temperature: ");
    Serial.println(tempC, DEC);
    
    // Play the first file
    playfile(String("temp.wav"));
  
    // File name to read?
    if (tempC > 20)
    {
      Serial.print("Open filename ");
      String filename1 =  String(String(tempC - (tempC % 10)) + ".wav");
      Serial.println(filename1);
      playfile(filename1);    
    
      Serial.print("Open filename ");
      String filename2 =  String(String(tempC % 10) + ".wav");
      Serial.println(filename2);
      playfile(filename2);  
    }
    else
    {
      Serial.print("Open filename ");
      String filename =  String(String(tempC) + ".wav");
      Serial.println(filename);
      playfile(filename);
    }
  }
  else
  {
    // Button was not pressed, sleep for a bit
    delay(50);  
  }

}

void playfile(String filename)
{
  const int S=1024; // Number of samples to read in block
  short buffer[S];
  char chfilename[20];
  
  filename.toCharArray(chfilename, 20);
 
  // Open first wave file from sdcard
  File myFile = SD.open(chfilename, FILE_READ);
  if (!myFile)
  {
    // If the file could not be opened, halt
    Serial.print("Error opening file: ");
    Serial.println(filename);
    while (true);
  }

  // Loop the contents of the file
  while (myFile.available())
  {
    // Read from the file into buffer
    myFile.read(buffer, sizeof(buffer));

    // Prepare samples
    int volume = 1023;
    Audio.prepare(buffer, S, volume);
    // Feed samples to audio
    Audio.write(buffer, S);
  }
  myFile.close();  
}
