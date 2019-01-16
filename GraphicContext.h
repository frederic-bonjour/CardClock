#ifndef _GraphicContext_H_
#define _GraphicContext_H_

#include <Arduino.h>

#include "Font.h"

enum TextAlign { LEFT, CENTER, RIGHT };
enum Intensity { Min = 1, Low = 3, Medium = 5, High = 10, Max = 15 };

class GraphicContext {

  protected:
    byte width, height;
    Intensity intensity = Medium;
    Font* font;

  public:

    GraphicContext(byte w, byte h);
    ~GraphicContext();

    GraphicContext* setIntensity(Intensity i);

    GraphicContext* setPixel(int8_t x, int8_t y, bool on = true);
    GraphicContext* clear();
    byte drawChar(int8_t x, int8_t y, char c);
    GraphicContext* text(int8_t x, int8_t y, String text, TextAlign align = LEFT);
    uint16_t getTextWidth(String text);

    byte getBitMaskMaxWidth(byte* mask, byte h);
    GraphicContext* drawBitMask(int8_t x, int8_t y, byte* mask, byte w, byte h);

    GraphicContext* rectangle(int8_t x, int8_t y, int8_t w, int8_t h);

    byte getWidth();
    byte getHeight();

    byte getCenterY();
    byte getCenterX();
};

#endif
