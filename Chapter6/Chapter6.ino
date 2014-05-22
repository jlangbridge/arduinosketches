#include <EEPROM.h>

#define EEPROM_DATAPOS 0
#define EEPROM_AGEPOS 1
#define EEPROM_NAMEPOS 2

#define EEPROM_CONTROL 42

char myName[] = {"Arduino"};
char userName[64];
char userAge[32];
unsigned char age;
int i;
byte myValue = 0;

void setup() {
  // Configure the serial port:
  Serial.begin(9600);
  
  // Does the EEPROM have any information?
  myValue = EEPROM.read(0);

  if (myValue == 42)
  {
    // Get the user's name
    for (i = 0; i < sizeof(userName); i++)
    {
      userName[i] = EEPROM.read(EEPROM_NAMEPOS + i);
    }
    
    // Get the user's age
    age = EEPROM.read(EEPROM_AGEPOS);

    // Print out what we know of the user
    Serial.println("I know you!");
    Serial.print("Your name is ");
    Serial.print(userName);
    Serial.print(" and you are ");
    Serial.print(age);
    Serial.println(" years old.");
    
    // Write zero back to the control number
    EEPROM.write(EEPROM_DATAPOS, 0);
  }
  else
  { 
    // Welcome the user
    Serial.println("Hello! What is your name?");
  
    // Wait until serial data is available
    while(!Serial.available())
    // Wait for all the data to arrive
    delay(200);
    
    // Read in serial data, one byte at a time
    Serial.readBytes(userName, Serial.available());
  
    // Say hello to the user
    Serial.print("Hello, ");
    Serial.print(userName);
    Serial.print(". My name is ");
    Serial.print(myName);
    Serial.println("\n");
    
    // Save the user's name to EEPROM
    for (i = 0; i < sizeof(userName); i++)
    {
        EEPROM.write(EEPROM_NAMEPOS + i, userName[i]);
    }
  
    // Ask for user's age
    Serial.print("How old are you, ");
    Serial.print(userName);
    Serial.println("?");
  
    // Wait for a few seconds, then read the serial buffer
    while(!Serial.available())
    // Wait for all the data to arrive
    delay(200);    
    age = Serial.parseInt();
  
    // Print out the user's age
    Serial.print("Oh, you are ");
    Serial.print(age);
    Serial.println("?");
    Serial.print("I am ");
    Serial.print(millis());
    Serial.println(" microseconds old. Well, my sketch is.");
    
    // Now save this to EEPROM memory
    EEPROM.write(EEPROM_AGEPOS, age);
    
    // Since we have all the information we need, and it has been saved, write a control number to EEPROM
    EEPROM.write(EEPROM_DATAPOS, EEPROM_CONTROL);
  }

}

void loop()
{
  // put your main code here, to run repeatedly: 
}
