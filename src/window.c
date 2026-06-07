#include "../include/window.h"
#include "../include/customColors.h"
#include "../include/grid.h"
#include <ncurses.h>

void sidebarWinInit(win *w, int h, int wid) {
  w->win2.h = h;
  w->win2.w = wid;

  return;
}

void winInit(win *window) {

  int rows = window->rows;
  int cols = window->cols;

  WINDOW *root = window->root;

  int mainHeight = rows - 2;
  int leftWidth = cols * 75 / 100;
  int rightWidth = cols - leftWidth;

  window->win1.window = derwin(root, window->rows, leftWidth, 0, 0);
  gridWinInit(&window->win1, mainHeight, leftWidth);

  window->win2.win = derwin(root, mainHeight, rightWidth, 0, leftWidth);
  sidebarWinInit(window, mainHeight, rightWidth);

  window->win4 = derwin(root, 2, rightWidth, mainHeight, leftWidth);

  window->cmd = derwin(root, 1, leftWidth, mainHeight + 1, 0);
  wbkgd(window->cmd, COLOR_PAIR(secondaryBg));

  return;
};

void rootInit(win *w) {
  w->root = newwin(w->rows, w->cols, 0, 0);

  winInit(w);
  wrefresh(w->win1.window);
  wrefresh(w->win2.win);
  wrefresh(w->win4);
  wrefresh(w->cmd);

  return;
}
