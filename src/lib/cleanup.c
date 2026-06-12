#include "../../include/lib/cleanup.h"
#include <stdlib.h>

void quit(win *w) {
  if (w->win[POPUP])
    delwin(w->win[POPUP]);

  if (w->win[INFO])
    delwin(w->win[INFO]);

  if (w->win[GRID])
    delwin(w->win[GRID]);

  if (w->win[SIDEBAR])
    delwin(w->win[SIDEBAR]);

  if (w->win[ROOT])
    delwin(w->win[ROOT]);

  if (w->extras.warningText)
    free(w->extras.warningText);

  if (w->win1.cells)
    free(w->win1.cells);

  if (w->win1.tempCells)
    free(w->win1.tempCells);

  if (w->win1.info.colors)
    free(w->win1.info.colors);

  if (w->xterm)
    free(w->xterm);

  endwin();
}
