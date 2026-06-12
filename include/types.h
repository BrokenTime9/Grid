#ifndef TYPES_H
#define TYPES_H

#include "./command/undo.h"
#include "./themes/theme.h"
#include <ncurses.h>
#include <stdbool.h>

typedef struct {
  int x;
  int y;

} cords;

typedef struct {

  int cols; // no of colms
  int rows; // no of rows
  int h;    // height of cell
  int w;    // width of cell
            //
  int tempW;
  int tempH;

  colorInfo *colors;
  short colorCount;
  short colorCapCount;
  short prevColor;

} gridInfo;

typedef struct {

  bool resize;
  bool cmd;
  bool warning;
  char *warningText;

} extras;

typedef struct {
  cords tl;
  cords br;
} cellInfo;

typedef struct {

  bool isSelected;
  color color;

  cellInfo info;
  cellInfo tempInfo;

} cell;

typedef struct {
  int h;
  int w;
  int maxh;
  int maxw;

  int cursor;
  int totalCells;

  cell *cells;
  cell *tempCells;

  gridInfo info;

} win1;

typedef struct {
  int h;
  int w;
} win2;

typedef struct {
  int width;
  int height;

} winSize;

typedef struct {
  // main rows and cols
  int rows;
  int cols;

  // window inits
  WINDOW *win[7];
  winSize winSize[7];

  // window sizes

  // main window / subwindow
  win1 win1;
  win2 win2;

  // extras
  extras extras;
  color *xterm;

  // command List for undo and redo;
  CmdList commands;
} win;

enum { ROOT = 0, GRID, SIDEBAR, INFO, POPUP, INFOPOPUP, CMD };

#endif // ndef TYPES_H
