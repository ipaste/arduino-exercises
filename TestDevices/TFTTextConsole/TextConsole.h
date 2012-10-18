#ifndef TextConsole_H
#define TextConsole_H

#define CURSOR_UNIT_X 6 
#define CURSOR_UNIT_Y 10

#define SCREEN_X 240
#define SCREEN_Y 320

#define TEXT_X 40
#define TEXT_Y 32

class TextConsole {
  private:
    int cursor_x; // graphical position of the cursor, counted by cursor unit
    int cursor_y;
    int cursor_idx_x; // textual position of the cursor, position of the string buffer
    int cursor_idx_y;
    
    char stringBuffer[TEXT_X][TEXT_Y];
    
    void drawByte(char b, int tX, int tY, int color);
  public:
    TextConsole();
    ~TextConsole();
    void writeByte(char b);
    void newLine();
    void moveUpOneLine();
    void moveCursorUpOneLine();
};

#endif
