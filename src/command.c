
#include "../include/types.h"
#include <ncurses.h>

int command(win *w) {
  wresize(w->win1.window, w->rows - 2, w->cols * 0.75);
  mvwin(w->cmd, w->rows - 2, 0);
  return 0;
};
