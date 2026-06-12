#include "../../include/lib/warning.h"
#include "../../include/themes/customColors.h"
#include "../../include/themes/theme.h"
#include "../../include/types.h"
#include <ncurses.h>

void customColors(Theme theme, color *xterm) {

  init_pair(primaryText, hexToXterm(theme.text, xterm),
            hexToXterm(theme.background, xterm));

  init_pair(primaryBg, hexToXterm(theme.text, xterm),
            hexToXterm(theme.background, xterm));

  init_pair(secondaryBg, hexToXterm(theme.text, xterm),
            hexToXterm(theme.secondary, xterm));

  init_pair(bordr, hexToXterm(theme.border, xterm),
            hexToXterm(theme.background, xterm));

  init_pair(cursor, hexToXterm(theme.cursor, xterm),
            hexToXterm(theme.cursor, xterm));

  init_pair(selected, hexToXterm(theme.selected, xterm),
            hexToXterm(theme.selected, xterm));

  init_pair(warn, hexToXterm(theme.warning, xterm),
            hexToXterm(theme.secondary, xterm));
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

int colorPair(win *w, color color) {
  int xterm = bitToXterm(color, w->xterm);

  int start = limit;
  int end = w->win1.info.colorCapCount;

  for (int i = start; i < end; i++) {

    if (w->win1.info.colors[i].isUsed) {
      if (w->win1.info.colors[i].xtermColor == xterm) {
        return w->win1.info.colors[i].colorPair;
      }
    }
  }

  SetWarning(w, "caching color...", "", 0);

  int pair = w->win1.info.colorCount;

  if (pair < start || pair >= end) {
    pair = start;
  }

  w->win1.info.colorCount = pair + 1;
  if (w->win1.info.colorCount < start || w->win1.info.colorCount >= end) {
    w->win1.info.colorCount = start;
  }

  w->win1.info.colors[pair].isUsed = true;
  w->win1.info.colors[pair].colorPair = pair;
  w->win1.info.colors[pair].xtermColor = xterm;
  w->win1.info.colors[pair].r = color.r;
  w->win1.info.colors[pair].g = color.g;
  w->win1.info.colors[pair].b = color.b;
  init_pair(pair, xterm, xterm);

  return pair;
}
