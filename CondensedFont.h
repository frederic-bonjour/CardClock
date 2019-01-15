#ifndef _CondensedFont_H_
#define _CondensedFont_H_

#include <Arduino.h>

#include "Font.h"
#include "Singleton.h"

#define CondensedFontCharCount 60

class CondensedFont : public Font, public Singleton<CondensedFont>
{
  friend class Singleton<CondensedFont>;

  private:

    static byte chars[CondensedFontCharCount][8];
    CondensedFont();

  public:

    byte  getHeight();
    bool  handlesDiacritics();
    byte  getCharWidth(char c);
    byte  getCharIndex(char c);
    byte* getChar(char c);
};

#endif