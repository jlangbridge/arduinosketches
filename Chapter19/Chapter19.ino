#include <Scheduler.h>

const int sensorPin = A0; // The analog input pin
const int powerPin = 7; // The power socket output pin

const int maxTemp = 26; // Turn off heater when above
const int minTemp = 24; // Turn on heater when below

int powerPinStatus = LOW; // By default, no power

int i; // Temporary variable

void setup()
{
  // Serial output at 9600 baud
  Serial.begin(9600);
  
  // Configure sensor pin
  pinMode(sensorPin, INPUT);
  
  // Start heater and lighting treads
  Scheduler.startLoop(heatloop);
  Scheduler.startLoop(lightloop);
}

void loop()
{
  yield();
}

// The loop responsible for checking water temperature
void heatloop()
{
  // Get a temperature reading from the temperature sensor
  int tempC = ( 3.3 * analogRead(sensorPin) * 100.0) / 1024.0; // 3.3V on the due
  
  // Send the temperature reading to the serial port
  Serial.print("Temperature: ");
  Serial.println(tempC);
  
  // Check to see if we need to change the output
  if (powerPinStatus == LOW)
  {
    //Mains plug currently turned off
    if (tempC < minTemp)
    {
      powerPinStatus = HIGH;
      digitalWrite(powerPin, powerPinStatus);
    }
  }
  else
  {
    // Mains plug currently turned on
    if (tempC > maxTemp)
    {
      powerPinStatus = LOW;
      digitalWrite(powerPin, powerPinStatus);
    }
  }
  
  // Warn if possible heating element failure
  if (tempC < (minTemp - 2))
    Serial.println("CRITICAL: Water temperature too low. Heating element failure?");
  
  // Sleep for ten seconds
  delay(10000);
}

// The loop responsible for lighting
void lightloop()
{
  // Wait for 7 hours before turning the lights off
  delay(7 * 60* 60 * 1000);
  
  // Lower the light level over the span of one hour
  for (i = 1023; i >= 0; i--)
  {
    analogWrite(DAC0, i);  // Write the light level to DAC0
    delay(60 * 60 * 1000 / 1024); //Sleep for a few seconds
  }
  
  // Wait for 11 hours
  delay(11 * 60* 60 * 1000);

  // Increase the light level over the span of one hour
  for (i = 0; i <= 1023; i++)
  {
    analogWrite(DAC0, i);  // Write the light level to DAC0
    delay(60 * 60 * 1000 / 1024); //Sleep for a few seconds
  }  
  
  //Wait for 4 hours
  delay(4 * 60* 60 * 1000);  
}
