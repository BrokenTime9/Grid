#include "../../include/lib/refresh.h"
#include "../../include/render/render.h"
#include <ncurses.h>

void refreshWin1(win *w) {

  werase(w->win[GRID]);
  if (w->extras.resize) {
    tempGridRender(w);
  } else {
    gridRender(w);
  }
  wrefresh(w->win[GRID]);
}

void refreshWin2(win *w) {

  werase(w->win[SIDEBAR]);
  sidebarRender(w);
  wrefresh(w->win[SIDEBAR]);
}

void refreshWin4(win *w) {

  werase(w->win[INFO]);
  infoWinRender(w);
  wrefresh(w->win[INFO]);
}
