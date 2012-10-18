#include "TextConsole.h"
#include "TFT.h"


TextConsole *console = new TextConsole(); // initialize the Text Console

void setup() {
  Tft.init(); // initialize the Tft screen
  Serial.begin(9600);
}


void loop() {
  char incomingByte;
  
  if (Serial.available() > 0) {   // something came across serial
    while(1) { // force into a loop until '\n' is received
      incomingByte = Serial.read();
      if(incomingByte == '@')  { // move up a line
        console->moveUpOneLine();
        console->moveCursorUpOneLine(); // it's neccessary because the following '\n' 
                                        // will move down a line
        continue;
      }
      if(incomingByte == '`') { // clear the screen
        console->reset();
        console->moveCursorUpOneLine(); // it's neccessary because the following '\n' 
                                        // will move down a line
        continue;
      }
      
      if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1   
      
      if(incomingByte != '\n') {
        console->writeByte(incomingByte);
      } else {
        console->newLine(); break; // break the while loop if the line from Serial ends
      }
    }
  }
}

