#include <KeyboardController.h>

// Key pressed
int curkeycode = 0;

// Initialize USB Controller
USBHost usb;

// Attach keyboard controller to USB
KeyboardController keyboard(usb);

void setup()
{
  Serial.begin(9600);
  Serial.println("Program started");
  delay(200);
}

void loop()
{
  keyloop();
}

// This function intercepts key press
void keyPressed()
{
  curkeycode = keyboard.getKey();
}

// Sort the final sentence
void sortSentence(String sentence)
{
  // Sentence logic goes here
  Serial.println(sentence);
}

void keyloop()
{
  String sentence = "";
  bool waitforkey = true;

  while (waitforkey == true)
  {
    // Process USB tasks
    usb.Task();
    
    // ASCII char  
    if (curkeycode >= 97 && curkeycode <= 122)
    {
      sentence += char(curkeycode);
      Serial.write(curkeycode);
    }
    
    // Return
    else if (curkeycode == 19)
    {
      Serial.println();
      sortSentence(sentence);
      waitforkey = false;
    }
    
    curkeycode = 0;
  }  
}

