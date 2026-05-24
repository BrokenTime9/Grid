#include "../include/popup.h"
#include "../include/export.h"
#include <ncurses.h>

int confirmWin(win *window) {
  int h = 3;
  int w = 70;

  int y = (window->rows - h) / 2;
  int x = (window->cols - w) / 2;

  int yx = w * 0.25;
  int nx = w - yx * 2;

  window->popup = newwin(h, w, y, x);

  wbkgd(window->popup, COLOR_PAIR(1));

  box(window->popup, 0, 0);

  wattron(window->popup, COLOR_PAIR(1) | A_BOLD);
  mvwprintw(window->popup, 0, 2, " Would you like to extract the cords? ");

  mvwprintw(window->popup, 2, yx, " Y : Yes ");

  mvwprintw(window->popup, 2, nx, " N : No ");
  wattroff(window->popup, COLOR_PAIR(1) | A_BOLD);

  wrefresh(window->popup);

  int ch;
  while (1) {
    ch = getch();
    if (ch == 'n') {

      werase(window->popup);
      wrefresh(window->popup);
      delwin(window->popup);

      touchwin(window->root);

      wrefresh(window->root);
      wrefresh(window->win1.window);
      wrefresh(window->win2.win);
      wrefresh(window->win4);

      return 0;
    }
    if (ch == 'y') {
      exportCoords(window);
      return 1;
    }
  }
};

int valueSetter(win *window) {
  int h = 3;
  int w = 70;

  int y = (window->rows - h) / 2;
  int x = (window->cols - w) / 2;

  int yx = w * 0.25;
  int nx = w - yx * 2;

  window->valuePopup = newwin(h, w, y, x);

  wbkgd(window->valuePopup, COLOR_PAIR(1));

  box(window->valuePopup, 0, 0);

  wattron(window->valuePopup, COLOR_PAIR(1) | A_BOLD);
  mvwprintw(window->valuePopup, 0, 2, " Would you like to set the values? ");

  mvwprintw(window->valuePopup, 2, yx, " Y : Yes ");

  mvwprintw(window->valuePopup, 2, nx, " N : No ");
  wattroff(window->valuePopup, COLOR_PAIR(1) | A_BOLD);

  wrefresh(window->valuePopup);

  int ch;
  while (1) {
    ch = getch();
    if (ch == 'n') {
      return 1;
    }
    if (ch == 'y') {

      werase(window->valuePopup);
      wrefresh(window->valuePopup);
      delwin(window->valuePopup);

      window->win1.info.w = 2;
      window->win1.info.h = 2;
      window->win1.info.cols = 2;
      window->win1.info.rows = 2;

      touchwin(window->root);

      wrefresh(window->root);
      wrefresh(window->win1.window);
      wrefresh(window->win2.win);
      wrefresh(window->win4);

      return 0;
    }
  }
};
