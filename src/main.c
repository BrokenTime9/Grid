#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

#include "../include/cleanup.h"
#include "../include/customColors.h"
#include "../include/grid.h"
#include "../include/movement.h"
#include "../include/popup.h"
#include "../include/render.h"
#include "../include/window.h"
#include <unistd.h>

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

  Theme theme;

  char *themefile = "themes/theme6.toml";
  loadTheme(themefile, &theme);

  if (!loadTheme(themefile, &theme)) {
    fprintf(stderr, "Failed to load theme\n");
    return 1;
  }

  customColors(theme);

  win root;

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
  gridRender(&root.win1);
  sidebarRender(&root);

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
      cursorMove(ch, &root.win1);
      updateStatusBar(&root);

      if (root.win1.extras.resize) {
        tempGridRender(&root.win1);
      } else {
        gridRender(&root.win1);
      }
    }

    // resize
    if (ch == 'r') {
      root.win1.extras.resize = false;
      gridRender(&root.win1);
      root.win1.info.tempW = root.win1.info.w;
      root.win1.info.tempH = root.win1.info.h;
    }
    if (ch == KEY_UP) {

      root.win1.extras.resize = true;
      if (root.win1.info.tempH - 1 >= 1) {
        root.win1.info.tempH = root.win1.info.tempH - 1;
        tempCellInit(&root.win1);
        tempGridRender(&root.win1);
      }
    }

    if (ch == KEY_DOWN) {

      root.win1.extras.resize = true;
      root.win1.info.tempH = root.win1.info.tempH + 1;
      tempCellInit(&root.win1);
      tempGridRender(&root.win1);
    }

    if (ch == KEY_LEFT) {

      root.win1.extras.resize = true;
      if (root.win1.info.tempW - 1 >= 1) {
        root.win1.info.tempW = root.win1.info.tempW - 1;
        tempCellInit(&root.win1);
        tempGridRender(&root.win1);
      }
    }

    if (ch == KEY_RIGHT) {

      root.win1.extras.resize = true;
      root.win1.info.tempW = root.win1.info.tempW + 1;
      tempCellInit(&root.win1);
      tempGridRender(&root.win1);
    }

    if (ch == 'x' || ch == 27) {
      selection(&root, ch);
      sidebarRender(&root);
    }
  }

  quit(&root);
  return 0;
}
