#ifndef _Font_H_
#define _Font_H_

#include <Arduino.h>

class Font
{
  private:

  public:

    virtual byte  getHeight();
    virtual bool  handlesDiacritics();
    virtual byte  getCharWidth(char c);
    virtual byte  getCharIndex(char c);
    virtual byte* getChar(char c);
};

#endif