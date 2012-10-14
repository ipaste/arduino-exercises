// Draw Texts - Demonstrate drawChar and drawString
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <stdint.h>
#include <TouchScreen.h> 
#include <TFT.h>

#ifdef SEEEDUINO
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 14   // can be a digital pin, this is A0
  #define XP 17   // can be a digital pin, this is A3 
#endif

#ifdef MEGA
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 54   // can be a digital pin, this is A0
  #define XP 57   // can be a digital pin, this is A3 
#endif 

int time = 0;
double baseMillis = 0;

int x = 0;
int y = 0;
int xMax = 240;
int yMax = Tft.height();

void setup()
{

Tft.init();  //init TFT library
Serial.begin(9600);
  Tft.drawString("ABCDEFGabcdefg",0,0,1,CYAN);
  Tft.drawString("ABCDEFGabcdefg",0,7,2,GREEN);
  Tft.drawString("ABCDEFG",0,21,3,RED);
  Tft.drawString("ABCDEFG",0,42,4,WHITE);
  Tft.drawString("ABCD",0,70,5,BLUE);
  Tft.drawString("ABC",0,105,6,YELLOW);
  
  baseMillis = millis()/1000.0f;
  xMax = Tft.height();
  yMax = Tft.width();
  Serial.println(baseMillis);
  Serial.print("Screen resolution: "); Serial.print(xMax); Serial.print("x");Serial.println(yMax);
}

void loop()
{
  for(int i = 0; i < xMax; i++) {
    for(int j = 0; j < yMax; j++) {
      Tft.setPixel(i, j, CYAN);
    }
  }
  
  double newMillis = millis()/1000.0f;
  Serial.println(newMillis);
  time++;
  if(time == 10) {
    Serial.print("rate: ");
    Serial.print((newMillis - baseMillis)/10.0f);
    Serial.println(" fps");
    baseMillis = newMillis;
    time = 0;
  }
}
