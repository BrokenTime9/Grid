#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

#include "../include/movement.h"
#include "../include/popup.h"
#include "../include/render.h"
#include "../include/window.h"

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

  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(2, COLOR_GREEN, COLOR_RED);

  win root;

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  if (argc == 5) {
    root.win1.info.rows = atoi(argv[1]);
    root.win1.info.cols = atoi(argv[2]);
    root.win1.info.h = atoi(argv[3]);
    root.win1.info.w = atoi(argv[4]);
  }

  if (argc != 5) {
    int shouldQuit = valueSetter(&root);
    if (shouldQuit) {
      return 1;
    }
  }

  rootInit(&root, cols, rows);
  gridRender(&root.win1);
  sidebarRender(&root);

  int ch;

  while (1) {

    ch = getch();

    if (ch == 'q')
      break;

    if (ch == 'e') {
      int shouldQuit = confirmWin(&root);

      if (shouldQuit) {
        break;
      }
    }

    if (ch == 'j' || ch == 'h' || ch == 'k' || ch == 'l') {
      cursorMove(ch, &root.win1);
      gridRender(&root.win1);
    }

    if (ch == 'x' || ch == 27) {
      selection(&root, ch);
      sidebarRender(&root);
    }
  }

  free(root.win1.cells);

  endwin();

  return 0;
}
