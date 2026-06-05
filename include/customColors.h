#ifndef CUSTOM_COLORS_H
#define CUSTOM_COLORS_H
#include "./theme.h"

// theme.h
#define THEME_BG 234
#define THEME_PANEL 236
#define THEME_BORDER 240
#define THEME_GREEN 46
#define THEME_ORANGE 208
#define THEME_RED 196
#define THEME_BLUE 39
#define THEME_YELLOW 226

enum {

  primaryText = 1,
  secondaryText,
  primaryBg,
  secondaryBg,
  bordr,
  cursor,
  selected,
  warning
};

void customColors(Theme theme);
int retDex(char x);
int hexToXterm(char *color);

#endif
