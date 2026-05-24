#ifndef TYPES_H
#define TYPES_H

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

} gridInfo;

typedef struct {
  cords tl;
  cords br;
} cellInfo;

typedef struct {

  bool isSelected;

  cellInfo info;

} cell;

typedef struct {
  int h;
  int w;
  WINDOW *window;

  int cursor;
  int totalCells;
  cell *cells;

  gridInfo info;

} win1;

typedef struct {
  int h;
  int w;

  WINDOW *win;

} win2;

typedef struct {
  int rows;
  int cols;

  WINDOW *root;
  win1 win1;
  win2 win2;
  WINDOW *win4;

  WINDOW *popup;
  WINDOW *valuePopup;
} win;

#endif // ndef TYPES_H
