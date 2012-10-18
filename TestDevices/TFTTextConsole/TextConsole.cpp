#include "TextConsole.h"
#include "TFT.h"

TextConsole::TextConsole() {
  
  this->cursor_x = 0; // textual position of the cursor, counted by cursor unit
  this->cursor_y = 0;
  
  for(int i = 0; i < TEXT_X; i++) // initialize the string buffer with '\0'
    for(int j = 0; j < TEXT_Y; j++)
      this->textBuffer[i][j] = '\0';
}

void TextConsole::drawByte(char b, int tX, int tY, int color) {
  int x = tX * CURSOR_UNIT_X;
  int y = tY * CURSOR_UNIT_Y;
  Tft.drawChar(b, x, y, 1, color);
}

void TextConsole::writeByte(char b) {
  // sets char in the buffer
  this->textBuffer[this->cursor_x][this->cursor_y] = b;
  
  // draws the byte
  this->drawByte(b, this->cursor_x, this->cursor_y, CYAN);
  
  // move the cursor to next position
  this->cursor_x++;
  
  // decides if need to add a new line
  if(this->cursor_x >= TEXT_X) {
    this->newLine();
  }
  
}

void TextConsole::newLine() {
  this->cursor_x = 0;
  this->cursor_y++;
  if(this->cursor_y >= TEXT_Y) { // need to move all the char in string 
                                 // buffer up one line, and refresh the screen 
    this->moveUpOneLine();
  }    
}

void TextConsole::moveUpOneLine() {
  int currentLine = this->cursor_y--; // get the current line number value, and 
                                      // set the line number variable to previous line
  
  // move text buffer
  for(int j = 0; j < currentLine - 1; j++) {
    for(int i = 0; i < TEXT_X; i++) {
      // black out byte on screen first
      if(this->textBuffer[i][j] != '\0' && this->textBuffer[i][j] != '\n')
        drawByte(this->textBuffer[i][j], i, j, BLACK);
      // move byte to the upper line
      this->textBuffer[i][j] = this->textBuffer[i][j+1];
      // draw the moved byte
      if(this->textBuffer[i][j] != '\0' && this->textBuffer[i][j] != '\n') 
        drawByte(this->textBuffer[i][j], i, j, CYAN); 
    }
  }
  
  for(int i = 0; i < TEXT_X; i++) { // clean the current line which is not included 
                                    // in the moving string loop
    char c = this->textBuffer[i][currentLine-1];
    // black out the preious char first
    if(c != '\0' && c != '\n')
      drawByte(c, i, currentLine-1, BLACK);
    this->textBuffer[i][currentLine-1] = '\0';
  }
  
}

void TextConsole::moveCursorUpOneLine() { // simply move the cursor up without redrawing
  this->cursor_y -= 1;
}

void TextConsole::reset() {
  Tft.fillRectangle(0,0,SCREEN_X,SCREEN_Y,BLACK); // slower than clear the text
  
//  for(int i = 0; i < TEXT_X; i++) 
//    for(int j = 0; j < this->cursor_y; j++)
//      if(this->textBuffer[i][j] != '\0' && this->textBuffer[i][j] != '\n') {
//        this->drawByte(this->textBuffer[i][j],i,j,BLACK);
//      }
  
  this->cursor_x = this->cursor_y = 0;
}
