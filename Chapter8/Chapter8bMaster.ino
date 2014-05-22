#include <Wire.h>

#define SLAVE_ADDRESS 0x08
int data = 0;
int state = 0;

void setup()
{
  pinMode(13, OUTPUT); // Internal LED
  Serial.begin(9600);
  Wire.begin(); // Initialize as I2C master
}

void loop()
{
  Wire.beginTransmission(SLAVE_ADDRESS); // Prepare message to slave
  Wire.write(1); // Send one byte, LED ON
  Wire.endTransmission(); // End message, transmit
  digitalWrite(13, HIGH); // Turn the LED on
  
  delay(10); // Give the slave time to react
  printLight(); // What is the slave's status?
  
  delay(1000);
  
  Wire.beginTransmission(SLAVE_ADDRESS); // Prepare message to slave
  Wire.write(0); // Send one byte, LED ON
  Wire.endTransmission(); // End message, transmit
 digitalWrite(13, LOW); // Turn the LED off 
   
  delay(10); // Give the slave time to react
  printLight(); // What is the slave's status?
  
  delay(200);
}

void printLight()
{
  Wire.requestFrom(SLAVE_ADDRESS, 1); // Request 1 byte from slave device
  
  data = Wire.read(); // Receive a byte af data
  switch (data)
  {
    case 0:
      Serial.println("LED is OFF");
      break;
    case 1:
      Serial.println("LED is ON");
      break;      
    default:
      Serial.println("Unknown status detected");
      break;
  }
}
