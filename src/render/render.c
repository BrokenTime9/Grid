#include "../../include/render/render.h"
#include "../../include/themes/customColors.h"
#include <ncurses.h>

void colorControl(win *w, WINDOW *win, int t, cell c) {
  // normal
  if (t == 0) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(win, j, i, ' ' | COLOR_PAIR(secondaryBg));
      }
    }
  }

  // selected
  if (t == 1) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(win, j, i, ' ' | COLOR_PAIR(colorPair(w, c.color)));
      }
    }
  }

  // cursor
  if (t == 2) {
    for (int i = c.info.tl.x; i <= c.info.br.x; i++) {
      for (int j = c.info.tl.y; j <= c.info.br.y; j++) {
        mvwaddch(win, j, i, ' ' | COLOR_PAIR(cursor));
      }
    }
  }
}

void gridRender(win *w) {
  // rendering the fence
  //
  werase(w->win[GRID]);

  for (int i = 0; i < w->win1.totalCells; i++) {
    cell *c = &w->win1.cells[i];

    int startX = c->info.tl.x;
    int startY = c->info.tl.y;

    int endX = c->info.br.x;
    int endY = c->info.br.y;

    if (startX == 1) {

      for (int y = startY; y <= endY; y++) {
        mvwaddch(w->win[GRID], y, startX - 1, '|' | COLOR_PAIR(bordr));
      }
    }

    if (startY == 1) {

      for (int x = startX; x <= endX; x++) {
        mvwaddch(w->win[GRID], startY - 1, x, '-' | COLOR_PAIR(bordr));
      }
    }

    for (int x = startX; x <= endX; x++) {
      mvwaddch(w->win[GRID], endY + 1, x, '-' | COLOR_PAIR(bordr));
    }

    for (int y = startY; y <= endY; y++) {
      mvwaddch(w->win[GRID], y, endX + 1, '|' | COLOR_PAIR(bordr));
    }

    mvwaddch(w->win[GRID], endY + 1, endX + 1, '+' | COLOR_PAIR(bordr));
    mvwaddch(w->win[GRID], startY - 1, startX - 1, '+' | COLOR_PAIR(bordr));

    if (c->isSelected == true) {
      colorControl(w, w->win[GRID], 1, w->win1.cells[i]);
    }

    if (i == w->win1.cursor) {
      colorControl(w, w->win[GRID], 2, w->win1.cells[i]);
    }
  }
  wrefresh(w->win[GRID]);
  return;
}

void tempGridRender(win *w) {
  // rendering the fence
  //

  werase(w->win[GRID]);
  for (int i = 0; i < w->win1.totalCells; i++) {
    cell *c = &w->win1.tempCells[i];
    cell *oc = &w->win1.cells[i];

    int startX = c->info.tl.x;
    int startY = c->info.tl.y;

    int endX = c->info.br.x;
    int endY = c->info.br.y;

    if (startX == 1) {

      for (int y = startY; y <= endY; y++) {
        mvwaddch(w->win[GRID], y, startX - 1, '|' | COLOR_PAIR(bordr));
      }
    }

    if (startY == 1) {

      for (int x = startX; x <= endX; x++) {
        mvwaddch(w->win[GRID], startY - 1, x, '-' | COLOR_PAIR(bordr));
      }
    }

    for (int x = startX; x <= endX; x++) {
      mvwaddch(w->win[GRID], endY + 1, x, '-' | COLOR_PAIR(bordr));
    }

    for (int y = startY; y <= endY; y++) {
      mvwaddch(w->win[GRID], y, endX + 1, '|' | COLOR_PAIR(bordr));
    }

    mvwaddch(w->win[GRID], endY + 1, endX + 1, '+' | COLOR_PAIR(bordr));
    mvwaddch(w->win[GRID], startY - 1, startX - 1, '+' | COLOR_PAIR(bordr));

    if (oc->isSelected == true) {
      colorControl(w, w->win[GRID], 1, w->win1.tempCells[i]);
    }

    if (i == w->win1.cursor) {
      colorControl(w, w->win[GRID], 2, w->win1.tempCells[i]);
    }
  }
  wrefresh(w->win[GRID]);
  return;
}

void sidebarRender(win *w) {
  werase(w->win[SIDEBAR]);

  wbkgd(w->win[SIDEBAR], COLOR_PAIR(primaryBg));

  wattron(w->win[SIDEBAR], COLOR_PAIR(bordr));
  box(w->win[SIDEBAR], 0, 0);
  wattroff(w->win[SIDEBAR], COLOR_PAIR(bordr));

  int starty = 1;
  int startx = 2;

  for (int i = 0; i < w->win1.totalCells; i++) {

    if (starty > w->win2.h - 2) {
      starty = 1;
      startx += 8;
    }

    if (startx > w->win2.w - 8 && starty > w->win2.h - 3) {
      mvwprintw(w->win[SIDEBAR], w->win2.h - 2, w->win2.w - 6, "...");
      break;
    }
    if (w->win1.cells[i].isSelected) {
      mvwprintw(w->win[SIDEBAR], starty, startx, "%d", i);

      starty++;
    }
  }

  wrefresh(w->win[SIDEBAR]);
  return;
}

void infoWinRender(win *w) {

  wbkgd(w->win[INFO], COLOR_PAIR(primaryBg));

  wattron(w->win[INFO], COLOR_PAIR(bordr));
  box(w->win[INFO], 0, 0);
  wattroff(w->win[INFO], COLOR_PAIR(bordr));

  wattron(w->win[INFO], COLOR_PAIR(primaryText));
  mvwprintw(w->win[INFO], 0, 2, "( %d %d )", w->win1.cursor % w->win1.info.w,
            w->win1.cursor / w->win1.info.w);
  mvwprintw(w->win[INFO], 0, 12, "HEIGHT: %d", w->win1.info.h);
  mvwprintw(w->win[INFO], 1, 12, "WIDTH: %d", w->win1.info.w);
  mvwprintw(w->win[INFO], 0, 25, "COLS: %d", w->win1.info.cols);
  mvwprintw(w->win[INFO], 1, 25, "ROWS: %d", w->win1.info.rows);
  mvwprintw(w->win[INFO], 1, 35, " F1 : help ");
  wattroff(w->win[INFO], COLOR_PAIR(primaryText));

  if (!w->win1.info.colors[w->win1.info.colorCount - 1].isUsed) {

    wattron(w->win[INFO], COLOR_PAIR(colorPair(w, hexTo3bit("#FFFFFF"))));
    mvwprintw(w->win[INFO], 1, 4, "   ");
    wattroff(w->win[INFO], COLOR_PAIR(colorPair(w, hexTo3bit("#FFFFFF"))));

  } else {

    colorInfo y = w->win1.info.colors[w->win1.info.colorCount - 1];
    color color = {y.r, y.g, y.b};

    mvwprintw(w->win[INFO], 1, 4, "   ");
    wattron(w->win[INFO], COLOR_PAIR(colorPair(w, color)));
    mvwprintw(w->win[INFO], 1, 4, "   ");
    wattroff(w->win[INFO], COLOR_PAIR(colorPair(w, color)));
  }

  wrefresh(w->win[INFO]);
}

void updateStatusBar(win *w) {
  mvwprintw(w->win[INFO], 0, 2, "         ");

  mvwprintw(w->win[INFO], 0, 2, "( %d %d )", w->win1.cursor % w->win1.info.cols,
            w->win1.cursor / w->win1.info.cols);

  mvwprintw(w->win[INFO], 0, 12, "HEIGHT: %d", w->win1.info.tempH);
  mvwprintw(w->win[INFO], 1, 12, "WIDTH: %d", w->win1.info.tempW);
  if (!w->win1.info.colors[w->win1.info.colorCount - 1].isUsed) {

    wattron(w->win[INFO], COLOR_PAIR(colorPair(w, hexTo3bit("#FFFFFF"))));
    mvwprintw(w->win[INFO], 1, 4, "   ");
    wattroff(w->win[INFO], COLOR_PAIR(colorPair(w, hexTo3bit("#FFFFFF"))));

  } else {

    colorInfo y = w->win1.info.colors[w->win1.info.colorCount - 1];
    color color = {y.r, y.g, y.b};

    mvwprintw(w->win[INFO], 1, 4, "   ");
    wattron(w->win[INFO], COLOR_PAIR(colorPair(w, color)));
    mvwprintw(w->win[INFO], 1, 4, "   ");
    wattroff(w->win[INFO], COLOR_PAIR(colorPair(w, color)));
  }

  wrefresh(w->win[INFO]);
}

void resizeCell(win *w, int ch) {
  if (ch == 'r') {
    gridRender(w);
  }
};
