char myName[] = {"Arduino"};
char userName[64];
char userAge[32];
int age;
int i;


void setup() {
  // Configure the serial port:
  Serial.begin(9600);
  
  // Welcome the user
  Serial.println("Hello! What is your name?");
  
  //Wait for a few seconds, then read the serial buffer
  delay(10000);
  Serial.readBytes(userName, 64);
  
  //Say hello to the user
  Serial.print("Hello, ");
  Serial.print(userName);
  Serial.print(". My name is ");
  Serial.print(myName);
  Serial.println("\n");
  
  //Ask for user's age
  Serial.print("How old are you, ");
  Serial.print(userName);
  Serial.println("?");
  
  //Wait for a few seconds, then read the serial buffer
  delay(10000);
  age = Serial.parseInt();
  
  //Print out the user's age
  Serial.print("Oh, you are ");
  Serial.print(age);
  Serial.println("?");
  Serial.print("I am ");
  Serial.print(millis());
  Serial.println(" microseconds old. Well, my sketch is.");
  
  //Now print out the alphabet
  Serial.println("I know my alphabet! Let me show you!");
  Serial.println("Letter\tDec\tHex\t");
  for (i = 'A'; i <= 'Z'; i++)
  {
    Serial.write(i);
    Serial.print('\t');
    Serial.print(i);
    Serial.print('\t');
    Serial.print(i, HEX);
    Serial.print('\t');  
    Serial.print('\n');  
  }
}

void loop()
{
  // put your main code here, to run repeatedly: 
}
