#include "../include/movement.h"
#include "../include/render.h"

void cursorMove(int ch, win1 *w) {
  switch (ch) {
  case 'j':
    if (w->cursor + w->info.cols < w->totalCells) {
      colorControl(w->window, 0, w->tempCells[w->cursor]);

      if (w->cells[w->cursor].isSelected) {
        colorControl(w->window, 1, w->tempCells[w->cursor]);
      }

      w->cursor = w->cursor + w->info.cols;

      colorControl(w->window, 2, w->tempCells[w->cursor]);
    }
    break;

  case 'h':
    if (w->cursor - 1 >= 0) {

      colorControl(w->window, 0, w->tempCells[w->cursor]);

      if (w->cells[w->cursor].isSelected) {
        colorControl(w->window, 1, w->tempCells[w->cursor]);
      }

      w->cursor = w->cursor - 1;

      colorControl(w->window, 2, w->tempCells[w->cursor]);
    }
    break;

  case 'k':

    if (w->cursor - w->info.cols >= 0) {

      colorControl(w->window, 0, w->tempCells[w->cursor]);

      if (w->cells[w->cursor].isSelected) {
        colorControl(w->window, 1, w->tempCells[w->cursor]);
      }

      w->cursor = w->cursor - w->info.cols;

      colorControl(w->window, 2, w->tempCells[w->cursor]);
    }
    break;

  case 'l':
    if (w->cursor + 1 < w->totalCells) {

      colorControl(w->window, 0, w->tempCells[w->cursor]);

      if (w->cells[w->cursor].isSelected) {
        colorControl(w->window, 1, w->tempCells[w->cursor]);
      }

      w->cursor = w->cursor + 1;

      colorControl(w->window, 2, w->tempCells[w->cursor]);
    }

    break;
  }

  return;
}

// work funcs
void selection(win *w, int ch) {
  int x = w->win1.cursor;

  w->win1.cells[x].isSelected = !w->win1.cells[x].isSelected;

  if (w->extras.resize == true) {

    tempGridRender(&w->win1);
  } else {

    gridRender(&w->win1);
  }

  return;
}
