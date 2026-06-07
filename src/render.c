#include "../include/render.h"
#include "../include/customColors.h"
#include <ncurses.h>

void colorControl(WINDOW *w, int t, cell c) {
  // normal
  if (t == 0) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(w, j, i, ' ' | COLOR_PAIR(secondaryBg));
      }
    }
  }

  // selected
  if (t == 1) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(w, j, i, ' ' | COLOR_PAIR(selected));
      }
    }
  }

  // cursor
  if (t == 2) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(w, j, i, ' ' | COLOR_PAIR(cursor));
      }
    }
  }
}

void gridRender(win1 *w) {
  // rendering the fence
  //
  werase(w->window);
  wrefresh(w->window);

  wbkgd(w->window, COLOR_PAIR(primaryBg));

  for (int i = 0; i < w->totalCells; i++) {
    cell *c = &w->cells[i];

    int startX = c->info.tl.x;
    int startY = c->info.tl.y;

    int endX = c->info.br.x;
    int endY = c->info.br.y;

    if (startX == 1) {

      for (int y = startY; y <= endY; y++) {
        mvwaddch(w->window, y, startX - 1, '|' | COLOR_PAIR(bordr));
      }
    }

    if (startY == 1) {

      for (int x = startX; x <= endX; x++) {
        mvwaddch(w->window, startY - 1, x, '-' | COLOR_PAIR(bordr));
      }
    }

    for (int x = startX; x <= endX; x++) {
      mvwaddch(w->window, endY + 1, x, '-' | COLOR_PAIR(bordr));
    }

    for (int y = startY; y <= endY; y++) {
      mvwaddch(w->window, y, endX + 1, '|' | COLOR_PAIR(bordr));
    }

    mvwaddch(w->window, endY + 1, endX + 1, '+' | COLOR_PAIR(bordr));
    mvwaddch(w->window, startY - 1, startX - 1, '+' | COLOR_PAIR(bordr));

    if (c->isSelected == true) {
      colorControl(w->window, 1, w->cells[i]);
    }

    if (i == w->cursor) {
      colorControl(w->window, 2, w->cells[i]);
    }
  }
  wrefresh(w->window);
  return;
}

void tempGridRender(win1 *w) {
  // rendering the fence
  //

  werase(w->window);
  for (int i = 0; i < w->totalCells; i++) {
    cell *c = &w->tempCells[i];
    cell *oc = &w->cells[i];

    int startX = c->info.tl.x;
    int startY = c->info.tl.y;

    int endX = c->info.br.x;
    int endY = c->info.br.y;

    if (startX == 1) {

      for (int y = startY; y <= endY; y++) {
        mvwaddch(w->window, y, startX - 1, '|' | COLOR_PAIR(bordr));
      }
    }

    if (startY == 1) {

      for (int x = startX; x <= endX; x++) {
        mvwaddch(w->window, startY - 1, x, '-' | COLOR_PAIR(bordr));
      }
    }

    for (int x = startX; x <= endX; x++) {
      mvwaddch(w->window, endY + 1, x, '-' | COLOR_PAIR(bordr));
    }

    for (int y = startY; y <= endY; y++) {
      mvwaddch(w->window, y, endX + 1, '|' | COLOR_PAIR(bordr));
    }

    mvwaddch(w->window, endY + 1, endX + 1, '+' | COLOR_PAIR(bordr));
    mvwaddch(w->window, startY - 1, startX - 1, '+' | COLOR_PAIR(bordr));

    if (oc->isSelected == true) {
      colorControl(w->window, 1, w->tempCells[i]);
    }

    if (i == w->cursor) {
      colorControl(w->window, 2, w->tempCells[i]);
    }
  }
  wrefresh(w->window);
  return;
}

void sidebarRender(win *w) {
  werase(w->win2.win);

  wbkgd(w->win2.win, COLOR_PAIR(primaryBg));

  wattron(w->win2.win, COLOR_PAIR(bordr));
  box(w->win2.win, 0, 0);
  wattroff(w->win2.win, COLOR_PAIR(bordr));

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

void infoWinRender(win *window) {

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

  wrefresh(window->win4);
}

void updateStatusBar(win *window) {
  mvwprintw(window->win4, 0, 2, "         ");

  mvwprintw(window->win4, 0, 2, "( %d %d )",
            window->win1.cursor % window->win1.info.cols,
            window->win1.cursor / window->win1.info.cols);

  wrefresh(window->win4);
}
void resizeCell(win *w, int ch) {

  if (ch == 'r') {
    gridRender(&w->win1);
  }
};
