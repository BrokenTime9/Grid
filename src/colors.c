#include "../include/customColors.h"
#include "../include/theme.h"
#include <ncurses.h>

void customColors(Theme theme) {

  init_pair(primaryText, hexToXterm(theme.text), hexToXterm(theme.background));
  init_pair(primaryBg, hexToXterm(theme.text), hexToXterm(theme.background));
  init_pair(secondaryBg, hexToXterm(theme.text), hexToXterm(theme.secondary));
  init_pair(bordr, hexToXterm(theme.border), hexToXterm(theme.background));
  init_pair(cursor, hexToXterm(theme.cursor), hexToXterm(theme.cursor));
  init_pair(selected, hexToXterm(theme.selected), hexToXterm(theme.selected));
  init_pair(warning, hexToXterm(theme.warning), hexToXterm(theme.background));
}

int retDex(char x) {

  if (x >= '0' && x <= '9') {
    return x - '0';
  }

  switch (x) {

  case 'A':
  case 'a':
    return 10;

  case 'B':
  case 'b':
    return 11;

  case 'C':
  case 'c':
    return 12;

  case 'D':
  case 'd':
    return 13;

  case 'E':
  case 'e':
    return 14;

  case 'F':
  case 'f':
    return 15;
  }
  return 0;
}

int hexToXterm(char *color) {

  int r = 16 * retDex(color[0]) + retDex(color[1]);
  int g = 16 * retDex(color[2]) + retDex(color[3]);
  int b = 16 * retDex(color[4]) + retDex(color[5]);

  int r_id = (r * 5 + 127) / 255;
  int g_id = (g * 5 + 127) / 255;
  int b_id = (b * 5 + 127) / 255;

  return 16 + 36 * r_id + 6 * g_id + b_id;
}
