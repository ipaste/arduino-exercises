#include "TextConsole.h"
#include "TFT.h"

TextConsole *console = new TextConsole();

void setup() {
  Tft.init();
  Serial.begin(9600);
}


void loop() {
  
  char incomingByte;
  
  if (Serial.available() > 0) {   // something came across serial
    while(1) {            // force into a loop until '\n' is received
      incomingByte = Serial.read();
//      if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
      if(incomingByte == '@')  {
        console->moveUpOneLine();
        console->moveCursorUpOneLine();
        continue;
      }
      if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1   
      
      if(incomingByte != '\n') {
        console->writeByte(incomingByte);
      } else {
        console->newLine(); 
      }
    }
    Serial.println("Refresh 1 time");
  }
}

