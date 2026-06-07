#ifndef CUSTOM_COLORS_H
#define CUSTOM_COLORS_H
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
  warn
};

void customColors(Theme theme);
int retDex(char x);
int hexToXterm(char *color);

#endif
