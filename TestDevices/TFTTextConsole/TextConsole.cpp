#include "TextConsole.h"
#include "TFT.h"

TextConsole::TextConsole() {
  this->cursor_x = 0; // graphical position of the cursor, counted by cursor unit
  this->cursor_y = 0;
  this->cursor_idx_x = 0; // textual position of the cursor, position of the string buffer
  this->cursor_idx_y = 0;
  
  for(int i = 0; i < TEXT_X; i++) // initialize the string buffer with '\0'
    for(int j = 0; j < TEXT_Y; j++)
      this->stringBuffer[i][j] = '\0';
}

void TextConsole::drawByte(char b, int tX, int tY, int color) {
  int x = tX * CURSOR_UNIT_X;
  int y = tY * CURSOR_UNIT_Y;
  Tft.drawChar(b, x, y, 1, color);
}

void TextConsole::writeByte(char b) {
  // sets char in the buffer
  int x = this->cursor_idx_x;
  int y = this->cursor_idx_y;
  this->stringBuffer[x][y] = b;
  
  // draws the byte
  Tft.drawChar(b, this->cursor_x, this->cursor_y, 1, CYAN);
  
  // move the cursor to next position
  this->cursor_idx_x++;
  this->cursor_x += CURSOR_UNIT_X;
  
  // decides if need to add a new line
  if(this->cursor_idx_x >= TEXT_X) {
    this->newLine();
  }
  
}

void TextConsole::newLine() {
  this->cursor_idx_x = 0;
  this->cursor_idx_y++;
  this->cursor_x = 0;
  this->cursor_y += CURSOR_UNIT_Y;
  if(this->cursor_idx_y >= TEXT_Y) { // need to move all the char in string 
                                     // buffer up one line, and refresh the screen 
                                     // 
    this->moveUpOneLine();
  }    
}

void TextConsole::moveUpOneLine() {
  int currentLine = this->cursor_idx_y;
//  // clear window
//  Tft.fillRectangle(0, 0, SCREEN_X, SCREEN_Y, BLACK)
  
  // move string buffer
  for(int j = 0; j < currentLine - 1; j++) {
    for(int i = 0; i < TEXT_X; i++) {
      // black out previous char first
      if(this->stringBuffer[i][j] != '\0' && this->stringBuffer[i][j] != '\n')
        drawByte(this->stringBuffer[i][j], i, j, BLACK);
      // move byte  
      this->stringBuffer[i][j] = this->stringBuffer[i][j+1];
      // draw the moving byte
      if(this->stringBuffer[i][j] != '\0' && this->stringBuffer[i][j] != '\n') 
        drawByte(this->stringBuffer[i][j], i, j, CYAN); 
    }
  }
  for(int i = 0; i < TEXT_X; i++) { // clean the last line
    char c = this->stringBuffer[i][currentLine-1];
    // black out the preious char first
    if(c != '\0' && c != '\n')
      drawByte(c, i, currentLine-1, BLACK);
    this->stringBuffer[i][currentLine-1] = '\0';
  }
  
  this->cursor_idx_y--; // set the text line index back to previous line
  this->cursor_y -= CURSOR_UNIT_Y;
}

void TextConsole::moveCursorUpOneLine() {
  this->cursor_y -= CURSOR_UNIT_Y;
  this->cursor_idx_y -= 1;
}
