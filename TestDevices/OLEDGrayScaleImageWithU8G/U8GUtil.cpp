#include "U8GUtil.h"


U8GUtil::U8GUtil(U8GLIB u8g) {
 this->u8gi = u8g; 
}

void U8GUtil::draw4LGrayBitmap(unsigned char *bitmap, int height, int width) {
  char originColor = u8gi.getColorIndex();
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width - 3; j+=4) {
      char c = pgm_read_byte(&bitmap[(i*width + j)/4]);
      
      // draw pixel 1
      u8gi.setColorIndex( (c & 0xC0 >> 6));
      u8gi.drawPixel(i, j);
      // draw pixel 2
      u8gi.setColorIndex( (c & 0x30 >> 4));
      u8gi.drawPixel(i, j + 1);
      // draw pixel 3
      u8gi.setColorIndex( (c & 0x0C >> 2));
      u8gi.drawPixel(i, j + 2);
      // draw pixel 4
      u8gi.setColorIndex( (c & 0x03));
      u8gi.drawPixel(i, j + 3);
      
    }
  }
  u8gi.setColorIndex(originColor);
}

