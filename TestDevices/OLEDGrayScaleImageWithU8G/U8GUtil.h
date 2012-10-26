
#ifndef U8GExt_H
#define U8GExt_H

#include "U8glib.h"

class U8GUtil {
  private:
  U8GLIB u8gi;
  
  public:
  U8GUtil(U8GLIB u8g);
  void draw4LGrayBitmap(unsigned char *bitmap, int height, int width);
};


#endif
