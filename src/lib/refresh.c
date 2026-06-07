#include "../../include/refresh.h"
#include "../../include/render.h"
#include <ncurses.h>

void refreshWin1(win *w) {

  werase(w->win1.window);
  if (w->extras.resize) {
    tempGridRender(&w->win1);
  } else {
    gridRender(&w->win1);
  }
  wrefresh(w->win1.window);
};

void refreshWin2(win *w) {

  werase(w->win2.win);
  sidebarRender(w);
  wrefresh(w->win2.win);
};

void refreshWin4(win *w) {

  werase(w->win4);
  infoWinRender(w);
  wrefresh(w->win4);
};
