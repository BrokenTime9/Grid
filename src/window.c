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

  window->win1.window = derwin(root, mainHeight, leftWidth, 0, 0);
  gridWinInit(&window->win1, mainHeight, leftWidth);

  window->win2.win = derwin(root, mainHeight, rightWidth, 0, leftWidth);
  sidebarWinInit(window, mainHeight, rightWidth);
  window->win4 = derwin(root, 2, rightWidth, mainHeight, leftWidth);

  wattron(window->win2.win, COLOR_PAIR(bordr));
  box(window->win2.win, 0, 0);
  wattroff(window->win2.win, COLOR_PAIR(bordr));

  wattron(window->win4, COLOR_PAIR(bordr));
  box(window->win4, 0, 0);
  wattroff(window->win4, COLOR_PAIR(bordr));

  wbkgd(window->win4, COLOR_PAIR(primaryBg));

  wattron(window->win4, COLOR_PAIR(primaryText));
  mvwprintw(window->win4, 0, 2, "( %d %d )",
            window->win1.cursor % window->win1.info.w,
            window->win1.cursor / window->win1.info.w);
  mvwprintw(window->win4, 0, 12, "HEIGHT: %d", window->win1.info.h);
  mvwprintw(window->win4, 1, 12, "WIDTH: %d", window->win1.info.w);
  mvwprintw(window->win4, 0, 25, "COLS: %d", window->win1.info.cols);
  mvwprintw(window->win4, 1, 25, "ROWS: %d", window->win1.info.rows);
  mvwprintw(window->win4, 1, 35, " F1 : help ");
  wattroff(window->win4, COLOR_PAIR(primaryText));

  window->cmd = derwin(root, 2, leftWidth, mainHeight, 0);

  wbkgd(window->cmd, COLOR_PAIR(secondaryBg));

  wattron(window->cmd, COLOR_PAIR(bordr));
  werase(window->cmd);
  box(window->cmd, 0, 0);
  wattroff(window->cmd, COLOR_PAIR(bordr));

  wattron(window->cmd, COLOR_PAIR(primaryText));
  mvwprintw(window->cmd, 0, 0, " F1 : help ");
  wattroff(window->cmd, COLOR_PAIR(primaryText));

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

void updateStatusBar(win *window) {
  mvwprintw(window->win4, 0, 2, "         "); // clear old text

  mvwprintw(window->win4, 0, 2, "( %d %d )",
            window->win1.cursor % window->win1.info.cols,
            window->win1.cursor / window->win1.info.cols);

  wrefresh(window->win4);
}
