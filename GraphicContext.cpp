#include <Arduino.h>
#include <math.h>

#include "LedControl.h"

#include "GraphicContext.h"
#include "CondensedFont.h"
#include "Font.h"


/**
 pin 4: DataIn 
 pin 3: CLK 
 pin 2: CS 
*/

#define DISPLAY_COUNT 4
LedControl D = LedControl(4, 3, 2, DISPLAY_COUNT);


GraphicContext::GraphicContext(byte w, byte h) {
  width = w;
  height = h;
  font = CondensedFont::get();
  
  // Wake all the MAX72XX up.   
  for (byte b=0; b<DISPLAY_COUNT; b++) {
    D.shutdown(b, false);
    D.setIntensity(b, 8);
    D.clearDisplay(b);
  }
}


GraphicContext::~GraphicContext() {
}


byte GraphicContext::getWidth() {
  return width;
}


byte GraphicContext::getHeight() {
  return height;
}


byte GraphicContext::getCenterX() {
  return width / 2;
}


byte GraphicContext::getCenterY() {
  return height / 2;
}


GraphicContext* GraphicContext::setPixel(int8_t x, int8_t y, bool on) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return this;
  }
  if (y & 1) {
    //x = width - 1 - x;
  }
  
  byte matrix = x / 8;
  x = x % 8;
  D.setLed(matrix, y, x, on);
  
  return this;
}


GraphicContext* GraphicContext::rectangle(int8_t x, int8_t y, int8_t w, int8_t h) {
  for (int8_t i=x; i < x+w; i++) {
    this->setPixel(i, y)->setPixel(i, y+h);
  }
  for (int8_t i=y; i < y+h; i++) {
    this->setPixel(x, i)->setPixel(x+w, i);
  }
  return this;
}


GraphicContext* GraphicContext::clear() {
  for (byte b=0; b<DISPLAY_COUNT; b++) {
    D.clearDisplay(b);
  }
  return this;
}


byte GraphicContext::drawChar(int8_t x, int8_t y, char c) {
  byte* ch = font->getChar(c);

  if (ch != NULL) {
    byte h  = font->getHeight();
    byte cw = font->getCharWidth(c);

    for (byte l=0; l<h; l++) {
      byte def = ch[l];
      for (byte b=0; b<cw; b++) {
        if (def & (1<<b)) {
          this->setPixel((int8_t)(x + cw - 1 - b), (int8_t)(y + l));
        }
      }
    }

    return cw;
  }
  return 0;
}


GraphicContext* GraphicContext::text(int8_t x, int8_t y, String text, TextAlign align) {
  switch (align) {
    case RIGHT:
      x -= getTextWidth(text);
      break;
    case CENTER:
      x -= getTextWidth(text) / 2;
      break;
  }
  byte h  = font->getHeight();
  for (byte i=0; i<text.length(); i++) {
    char c = text.charAt(i);
    byte cw = font->getCharWidth(c);
    if ((x > -cw) && (x < width) && (y > -h) && (y < height)) {
      drawChar(x, y, c);
    }
    x += cw + 1;
  }
}


uint16_t GraphicContext::getTextWidth(String text) {
  byte width = 0;
  for (byte i=0; i<text.length(); i++) {
    width += font->getCharWidth(text.charAt(i)) + 1;
  }
  return width - 1;
}


GraphicContext* GraphicContext::drawBitMask(int8_t x, int8_t y, byte* mask, byte w, byte h) {
  for (byte yi=0; yi<h; yi++) {
    byte def = mask[yi];
    for (byte xi=0; xi<w; xi++) {
      setPixel(x + w - 1 - xi, y + yi, def & (1<<xi));
    }
  }
  return this;
}


byte GraphicContext::getBitMaskMaxWidth(byte* mask, byte h) {
  byte max = 0;
  for (byte l = 0; l < h; l++) {
    byte def = mask[l];
    for (byte b = 0; b < 8; b++) {
      if (def & (1 << b)) {
        if (b > max) {
          max = b;
        }
      }
    }
  }
  return max + 1;
}
