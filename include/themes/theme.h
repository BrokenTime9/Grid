#ifndef THEME_H
#define THEME_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {

  int r;
  int g;
  int b;

} color;

typedef struct {
  int r;
  int g;
  int b;

  short xtermColor;
  short colorPair;

  bool isUsed;

} colorInfo;

typedef struct {
  char background[7];
  char text[7];
  char border[7];
  char cursor[7];
  char selected[7];
  char warning[7];
  char secondary[7];
} Theme;

int loadTheme(char *path, Theme *theme, color *xterm);

#endif
