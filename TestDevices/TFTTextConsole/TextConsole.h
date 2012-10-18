#ifndef TextConsole_H
#define TextConsole_H

/*
 The default block size of a character (5x7 without space, 6x10 including space)
*/
#define CURSOR_UNIT_X 6 
#define CURSOR_UNIT_Y 10
/*
 The screen resolution is 240x320 by default display direction.
*/
#define SCREEN_X 240
#define SCREEN_Y 320
/* 
 The console resolution is 40x32 by default, with the font size 1 
 (6x10 pixels including spaces) 
*/
#define TEXT_X 40
#define TEXT_Y 32

class TextConsole {
  private:
    int cursor_x; // textual position of the cursor, position of the string buffer
    int cursor_y;
    
    char textBuffer[TEXT_X][TEXT_Y];
    
    void drawByte(char b, int tX, int tY, int color);
  public:
    TextConsole();
    ~TextConsole();
    void writeByte(char b);
    void newLine();
    void moveUpOneLine();
    void moveCursorUpOneLine();
    void reset();
};

#endif
