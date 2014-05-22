#include <Servo.h>

float tempC;
int angleC;
int reading;
int tempPin = 0;
int servoPin = 9;

Servo thServo;

void setup()
{
  analogReference(INTERNAL);
  Serial.begin(9600);
  thServo.attach(servoPin);
  thServo.write(90);
  delay(1000);
}

void loop()
{
  reading = analogRead(tempPin);
  tempC = reading / 9.31;
  angleC = map(tempC, 0, 40, 135, 45);
  Serial.print(tempC);
  Serial.print(" Celsius, ");
  Serial.print(angleC);
  Serial.println(" degrees");
  thServo.write(angleC);
  delay(500);
}
