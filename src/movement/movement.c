#include "../../include/movement/movement.h"
#include "../../include/render/render.h"
#include "../../include/themes/customColors.h"

void cursorMove(int ch, win *w) {
  switch (ch) {
  case 'j':
    if (w->win1.cursor + w->win1.info.cols < w->win1.totalCells) {
      colorControl(w, w->win[GRID], 0, w->win1.tempCells[w->win1.cursor]);

      if (w->win1.cells[w->win1.cursor].isSelected) {
        colorControl(w, w->win[GRID], 1, w->win1.tempCells[w->win1.cursor]);
      }

      w->win1.cursor = w->win1.cursor + w->win1.info.cols;

      colorControl(w, w->win[GRID], 2, w->win1.tempCells[w->win1.cursor]);
    }
    break;

  case 'h':
    if (w->win1.cursor - 1 >= 0) {

      colorControl(w, w->win[GRID], 0, w->win1.tempCells[w->win1.cursor]);

      if (w->win1.cells[w->win1.cursor].isSelected) {
        colorControl(w, w->win[GRID], 1, w->win1.tempCells[w->win1.cursor]);
      }

      w->win1.cursor = w->win1.cursor - 1;

      colorControl(w, w->win[GRID], 2, w->win1.tempCells[w->win1.cursor]);
    }
    break;

  case 'k':

    if (w->win1.cursor - w->win1.info.cols >= 0) {

      colorControl(w, w->win[GRID], 0, w->win1.tempCells[w->win1.cursor]);

      if (w->win1.cells[w->win1.cursor].isSelected) {
        colorControl(w, w->win[GRID], 1, w->win1.tempCells[w->win1.cursor]);
      }

      w->win1.cursor = w->win1.cursor - w->win1.info.cols;

      colorControl(w, w->win[GRID], 2, w->win1.tempCells[w->win1.cursor]);
    }
    break;

  case 'l':
    if (w->win1.cursor + 1 < w->win1.totalCells) {

      colorControl(w, w->win[GRID], 0, w->win1.tempCells[w->win1.cursor]);

      if (w->win1.cells[w->win1.cursor].isSelected) {
        colorControl(w, w->win[GRID], 1, w->win1.tempCells[w->win1.cursor]);
      }

      w->win1.cursor = w->win1.cursor + 1;

      colorControl(w, w->win[GRID], 2, w->win1.tempCells[w->win1.cursor]);
    }

    break;
  }

  return;
}

// work funcs
void selection(win *w, int ch) {
  int x = w->win1.cursor;

  w->win1.cells[x].isSelected = !w->win1.cells[x].isSelected;
  w->win1.tempCells[x].isSelected = !w->win1.tempCells[x].isSelected;

  if (w->win1.cells[x].isSelected) {
    if (w->win1.info.prevColor) {
      w->win1.cells[x].color = hexTo3bit("#FFFFFF");
      w->win1.tempCells[x].color = hexTo3bit("#FFFFFF");
    } else {
      colorInfo y = w->win1.info.colors[w->win1.info.colorCount - 1];
      w->win1.cells[x].color = (color){.r = y.r, .g = y.g, .b = y.b};
      w->win1.tempCells[x].color = (color){.r = y.r, .g = y.g, .b = y.b};
    }
  }

  if (w->extras.resize == true) {

    tempGridRender(w);
  } else {

    gridRender(w);
  }

  return;
}
