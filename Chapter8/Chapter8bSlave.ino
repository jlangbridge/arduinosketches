#include <Wire.h>

#define SLAVE_ADDRESS 0x08
int data = 0;
int state = 0;

void setup()
{
  pinMode(13, OUTPUT); // Internal LED
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS); // Initialize as I2C slave

  // Register I2C callbacks
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop()
{
  // Nothing to do
  delay(100);
}

// Callback for data reception
void receiveData(int byteCount)
{
  while(Wire.available())
  {
    data = Wire.read();
    Serial.print("Data received: ");
    Serial.println(data);

    if (data == 1)
    {
      digitalWrite(13, HIGH); // Turn the LED on
      state = 1;
    }
    else
    {
      digitalWrite(13, LOW); // Turn the LED off
      state = 0;
    }
  }
}

// Callback for sending data
void sendData()
{
    Wire.write(state); // Send the LED state
}
