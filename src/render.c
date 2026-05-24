#include "../include/render.h"

void colorControl(WINDOW *w, int t, cell c) {
  // normal
  if (t == 0) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(w, j, i, ' ');
      }
    }
  }

  // selected
  if (t == 1) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(w, j, i, ' ' | COLOR_PAIR(2));
      }
    }
  }

  // cursor
  if (t == 2) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(w, j, i, ' ' | COLOR_PAIR(1));
      }
    }
  }
}

void gridRender(win1 *w) {
  // rendering the fence
  //

  for (int i = 0; i < w->totalCells; i++) {
    cell *c = &w->cells[i];

    int startX = c->info.tl.x;
    int startY = c->info.tl.y;

    int endX = c->info.br.x;
    int endY = c->info.br.y;

    if (startX == 1) {

      for (int y = startY; y <= endY; y++) {
        mvwaddch(w->window, y, startX - 1, '|');
      }
    }

    if (startY == 1) {

      for (int x = startX; x <= endX; x++) {
        mvwaddch(w->window, startY - 1, x, '-');
      }
    }

    for (int x = startX; x <= endX; x++) {
      mvwaddch(w->window, endY + 1, x, '-');
    }

    for (int y = startY; y <= endY; y++) {
      mvwaddch(w->window, y, endX + 1, '|');
    }

    mvwaddch(w->window, endY + 1, endX + 1, '+');
    mvwaddch(w->window, startY - 1, startX - 1, '+');

    if (c->isSelected == true) {
      colorControl(w->window, 1, w->cells[i]);
    }

    if (i == w->cursor) {
      colorControl(w->window, 2, w->cells[i]);
    }
  }
  // visual render
  /*
  int startX = w->visStart % w->info.cols;
  int startY = w->visStart / w->info.cols;

  int endX = w->cursor % w->info.cols;
  int endY = w->cursor / w->info.cols;

  int minX = startX < endX ? startX : endX;
  int maxX = startX > endX ? startX : endX;

  int minY = startY < endY ? startY : endY;
  int maxY = startY > endY ? startY : endY;

  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {

      int index = y * w->info.cols + x;

      w->cells[index].isVisSelected = true;
      colorControl(w->window, 3, w->cells[index]);
    }
  }
  */

  wrefresh(w->window);
  return;
}

void sidebarRender(win *w) {
  werase(w->win2.win);
  box(w->win2.win, 0, 0);

  int starty = 1;
  int startx = 2;

  for (int i = 0; i < w->win1.totalCells; i++) {

    if (starty > w->win2.h - 2) {
      starty = 1;
      startx += 8;
    }

    if (startx > w->win2.w - 8 && starty > w->win2.h - 3) {
      mvwprintw(w->win2.win, w->win2.h - 2, w->win2.w - 6, "...");
      break;
    }
    if (w->win1.cells[i].isSelected) {
      mvwprintw(w->win2.win, starty, startx, "%d", i);

      starty++;
    }
  }

  wrefresh(w->win2.win);
  return;
}
