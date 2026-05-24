#include "../include/window.h"
#include "../include/grid.h"

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

  window->win1.window = derwin(root, mainHeight, leftWidth, 0, 0);
  gridWinInit(&window->win1, mainHeight, leftWidth);

  window->win2.win = derwin(root, mainHeight, rightWidth, 0, leftWidth);
  sidebarWinInit(window, mainHeight, rightWidth);
  window->win4 = derwin(root, 2, cols, mainHeight, 0);

  box(window->win2.win, 0, 0);
  box(window->win4, 0, 0);

  wattron(window->win2.win, COLOR_PAIR(1));
  mvwprintw(window->win2.win, 1, 2, "Window 2");
  wattroff(window->win2.win, COLOR_PAIR(1));

  wbkgd(window->win4, COLOR_PAIR(1));
  mvwprintw(window->win4, 0, 2, " X : toggle select ");
  mvwprintw(window->win4, 0, 23, " V : toggle visual ");
  mvwprintw(window->win4, 0, 44, " E : export cords ");
  mvwprintw(window->win4, 0, 64, " ESC : clear all ");
  mvwprintw(window->win4, 0, 82, " Q : quit ");

  return;
};

void rootInit(win *w, int cols, int rows) {
  w->cols = cols;
  w->rows = rows;
  w->root = newwin(rows, cols, 0, 0);

  winInit(w);
  wrefresh(w->win1.window);
  wrefresh(w->win2.win);
  wrefresh(w->win4);

  return;
}
