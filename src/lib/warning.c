#include "../../include/lib/refresh.h"
#include "../../include/themes/customColors.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void DisplayWarning(win *w) {

  keypad(w->win[CMD], TRUE);
  wresize(w->win[GRID], w->rows - 1, w->cols * 75 / 100);

  refreshWin1(w);

  werase(w->win[CMD]);

  wattron(w->win[CMD], COLOR_PAIR(warn));
  mvwprintw(w->win[CMD], 0, 1, "%s", w->extras.warningText);
  wattroff(w->win[CMD], COLOR_PAIR(warn));

  wrefresh(w->win[CMD]);

  getch();

  wresize(w->win[GRID], w->rows, w->cols * 75 / 100);
  wrefresh(w->win[GRID]);

  free(w->extras.warningText);
  w->extras.warningText = NULL;
  w->extras.warning = false;
};

void SetWarning(win *w, char *preWarn, char *postWarn, int mode) {
  char *warn;
  if (mode == 1) {
    size_t len = strlen(preWarn) + strlen(postWarn) + 1;

    warn = malloc(len);

    strcpy(warn, preWarn);
    strcat(warn, postWarn);
  } else {
    size_t len = strlen(preWarn) + 1;

    warn = malloc(len);

    strcpy(warn, preWarn);
  }

  w->extras.warningText = warn;
  w->extras.warning = true;
}
