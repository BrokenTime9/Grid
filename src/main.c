#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/command/command.h"
#include "../include/core/etc.h"
#include "../include/core/grid.h"
#include "../include/core/window.h"
#include "../include/lib/cleanup.h"
#include "../include/lib/warning.h"
#include "../include/movement/movement.h"
#include "../include/render/popup.h"
#include "../include/render/render.h"

int main(int argc, char *argv[]) {

  setlocale(LC_ALL, "");

  initscr();
  refresh();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);

  start_color();
  use_default_colors();

  win root;

  XtermColorPallete(&root);
  ThemeInit(&root);
  CommandInit(&root);

  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  root.cols = cols;
  root.rows = rows;
  root.win1.cells = NULL;

  if (argc == 5) {
    root.win1.info.rows = atoi(argv[1]);
    root.win1.info.cols = atoi(argv[2]);
    root.win1.info.h = atoi(argv[3]);
    root.win1.info.w = atoi(argv[4]);
  }

  if (argc != 5) {
    int shouldQuit = valueSetter(&root);
    if (shouldQuit) {
      quit(&root);
      return 0;
    }
    refresh();
  }
  curs_set(0);

  rootInit(&root);
  gridRender(&root);
  sidebarRender(&root);
  infoWinRender(&root);

  int ch;

  while (1) {

    ch = getch();

    // quit
    if (ch == 'q') {
      quit(&root);
      return 0;
    }

    // info
    if (ch == KEY_F(1)) {
      infoWin(&root);
    }
    if (ch == 'p') {
      printf("cells:     (%d,%d) -> (%d,%d)\n", root.win1.cells[1].info.tl.x,
             root.win1.cells[1].info.tl.y, root.win1.cells[1].info.br.x,
             root.win1.cells[1].info.br.y);

      printf("tempCells: (%d,%d) -> (%d,%d)\n",
             root.win1.tempCells[1].info.tl.x, root.win1.tempCells[1].info.tl.y,
             root.win1.tempCells[1].info.br.x,
             root.win1.tempCells[1].info.br.y);
    }

    // export
    if (ch == 'e') {
      int shouldQuit = confirmWin(&root);

      if (shouldQuit) {
        quit(&root);
        return 0;
      }
    }

    // move
    if (ch == 'j' || ch == 'h' || ch == 'k' || ch == 'l') {
      cursorMove(ch, &root);
      updateStatusBar(&root);

      if (root.extras.resize) {
        tempGridRender(&root);
      } else {
        gridRender(&root);
      }
    }

    // resize
    if (ch == 'r') {
      root.extras.resize = false;
      gridRender(&root);
      root.win1.info.tempW = root.win1.info.w;
      root.win1.info.tempH = root.win1.info.h;
    }
    if (ch == KEY_UP) {

      root.extras.resize = true;
      if (root.win1.info.tempH - 1 >= 1) {
        root.win1.info.tempH = root.win1.info.tempH - 1;
        tempCellInit(&root.win1);
        tempGridRender(&root);
        updateStatusBar(&root);
      }
    }

    if (ch == KEY_DOWN) {

      root.extras.resize = true;
      root.win1.info.tempH = root.win1.info.tempH + 1;
      tempCellInit(&root.win1);
      tempGridRender(&root);
      updateStatusBar(&root);
    }

    if (ch == KEY_LEFT) {

      root.extras.resize = true;
      if (root.win1.info.tempW - 1 >= 1) {
        root.win1.info.tempW = root.win1.info.tempW - 1;
        tempCellInit(&root.win1);
        tempGridRender(&root);
        updateStatusBar(&root);
      }
    }

    if (ch == KEY_RIGHT) {

      root.extras.resize = true;
      root.win1.info.tempW = root.win1.info.tempW + 1;
      tempCellInit(&root.win1);
      tempGridRender(&root);

      updateStatusBar(&root);
    }

    if (ch == 'x' || ch == 27) {
      selection(&root, ch);
      sidebarRender(&root);
    }

    if (ch == ':') {
      command(&root);
    }

    if (root.extras.warning && root.extras.warningText) {
      DisplayWarning(&root);
    }
  }

  quit(&root);
  return 0;
}
