#include "../../include/core/window.h"
#include "../../include/core/grid.h"
#include "../../include/themes/customColors.h"
#include <ncurses.h>

void sidebarWinInit(win *w, int h, int wid) {
  w->win2.h = h;
  w->win2.w = wid;

  return;
}

void winInit(win *w) {

  int rows = w->rows;
  int cols = w->cols;

  WINDOW *root = w->win[ROOT];
  /*
  w->winSize[GRID].width = 75;
  w->winSize[GRID].height = 100;

  w->winSize[SIDEBAR].width = 100 - w->winSize[GRID].width;
  w->winSize[SIDEBAR].height = 98;

  w->winSize[INFO].width = w->winSize[SIDEBAR].width;
  w->winSize[INFO].height = 100 - w->winSize[SIDEBAR].height;

  w->winSize[CMD].width = w->winSize[GRID].width;
  w->winSize[CMD].height = 1;

  int gridHeight = rows * w->winSize[GRID].height / 100;
  int gridWidth = cols * w->winSize[GRID].width / 100;

  int sidebarHeight = rows * w->winSize[SIDEBAR].height / 100;
  int sidebarWidth = cols * w->winSize[SIDEBAR].width / 100;

  int infoHeight =2;
  int infoWidth = cols * w->winSize[INFO].width / 100;

  int cmdHeight = rows * w->winSize[CMD].height / 100;
  int cmdWidth = cols * w->winSize[CMD].width / 100;

  */

  int mainHeight = rows - 2;
  int leftWidth = cols * 75 / 100;
  int rightWidth = cols - leftWidth;

  w->win[GRID] = derwin(root, w->rows, leftWidth, 0, 0);
  gridWinInit(&w->win1, mainHeight, leftWidth);
  wbkgd(w->win[GRID], COLOR_PAIR(primaryBg));

  w->win[SIDEBAR] = derwin(root, mainHeight, rightWidth, 0, leftWidth);
  sidebarWinInit(w, mainHeight, rightWidth);

  w->win[INFO] = derwin(root, 2, rightWidth, mainHeight, leftWidth);

  w->win[CMD] = derwin(root, 1, leftWidth, mainHeight + 1, 0);
  wbkgd(w->win[CMD], COLOR_PAIR(secondaryBg));

  return;
};

void rootInit(win *w) {
  w->win[ROOT] = newwin(w->rows, w->cols, 0, 0);

  winInit(w);
  wrefresh(w->win[GRID]);
  wrefresh(w->win[SIDEBAR]);
  wrefresh(w->win[INFO]);
  wrefresh(w->win[CMD]);

  return;
}
