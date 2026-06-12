#ifndef CUSTOM_COLORS_H
#define CUSTOM_COLORS_H
#include "../types.h"
#include "./theme.h"

// theme.h
enum {

  primaryText = 1,
  secondaryText,
  primaryBg,
  secondaryBg,
  bordr,
  cursor,
  selected,
  warn,
  limit
};

void customColors(Theme theme, color *xterm);
int retDex(char x);
int hexToXterm(char *hex, color *xterm);

color hexTo3bit(char *hex);
int bitToXterm(color clr, color *xterm);

int colorPair(win *w, color color);

// init
void mapColor(color *xterm);
int hexToXtermInit(char *hex, color *xterm);

#endif
