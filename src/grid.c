#include "../include/grid.h"
#include <stdlib.h>

void cellInit(win1 *w) {

  int prevColStart;
  int prevColEnd;
  int prevRowStart;
  int prevRowEnd;

  for (int row = 0; row < w->info.rows; row++) {
    for (int col = 0; col < w->info.cols; col++) {

      int index = row * w->info.cols + col;

      int startX;
      int startY;
      int endX;
      int endY;

      startX = col * w->info.w + 1;
      startY = row * w->info.h + 1;

      endX = col * w->info.w + w->info.w;
      endY = row * w->info.h + w->info.h;

      if (col != 0 && row == 0) {
        startX = prevColStart + w->info.w + 1;
        startY = row * w->info.h + 1;

        endX = prevColEnd + w->info.w + 1;
        endY = row * w->info.h + w->info.h;
      }
      if (row != 0 && col == 0) {
        startX = col * w->info.w + 1;
        startY = prevRowStart + w->info.h + 1;

        endX = col * w->info.w + w->info.w;
        endY = prevRowEnd + w->info.h + 1;
      }

      if (col != 0 && row != 0) {
        startX = prevColStart + w->info.w + 1;
        startY = prevRowStart;

        endX = prevColEnd + w->info.w + 1;
        endY = prevRowEnd;
      }

      w->cells[index].info.tl.x = startX;
      w->cells[index].info.tl.y = startY;

      w->cells[index].info.br.x = endX;
      w->cells[index].info.br.y = endY;

      w->cells[index].isSelected = false;

      prevColStart = startX;
      prevColEnd = endX;
      prevRowStart = startY;
      prevRowEnd = endY;
    }
  }
}

void tempCellInit(win1 *w) {

  int prevColStart;
  int prevColEnd;
  int prevRowStart;
  int prevRowEnd;

  for (int row = 0; row < w->info.rows; row++) {
    for (int col = 0; col < w->info.cols; col++) {

      int index = row * w->info.cols + col;

      int startX;
      int startY;
      int endX;
      int endY;

      startX = col * w->info.tempW + 1;
      startY = row * w->info.tempH + 1;

      endX = col * w->info.tempW + w->info.tempW;
      endY = row * w->info.tempH + w->info.tempH;

      if (col != 0 && row == 0) {
        startX = prevColStart + w->info.tempW + 1;
        startY = row * w->info.tempH + 1;

        endX = prevColEnd + w->info.tempW + 1;
        endY = row * w->info.tempH + w->info.tempH;
      }
      if (row != 0 && col == 0) {
        startX = col * w->info.tempW + 1;
        startY = prevRowStart + w->info.tempH + 1;

        endX = col * w->info.tempW + w->info.tempW;
        endY = prevRowEnd + w->info.tempH + 1;
      }

      if (col != 0 && row != 0) {
        startX = prevColStart + w->info.tempW + 1;
        startY = prevRowStart;

        endX = prevColEnd + w->info.tempW + 1;
        endY = prevRowEnd;
      }

      w->tempCells[index].info.tl.x = startX;
      w->tempCells[index].info.tl.y = startY;

      w->tempCells[index].info.br.x = endX;
      w->tempCells[index].info.br.y = endY;

      w->tempCells[index].isSelected = w->cells[index].isSelected;

      prevColStart = startX;
      prevColEnd = endX;
      prevRowStart = startY;
      prevRowEnd = endY;
    }
  }
  return;
}

void gridWinInit(win1 *win, int h, int w) {

  win->h = h - 2;
  win->w = w - 2;

  win->info.tempH = win->info.h;
  win->info.tempW = win->info.w;

  win->totalCells = win->info.cols * win->info.rows;

  win->cursor = 0;
  win->cells = malloc(sizeof(cell) * win->totalCells);
  win->tempCells = malloc(sizeof(cell) * win->totalCells);

  cellInit(win);

  for (int i = 0; i < win->info.rows; i++) {
    for (int j = 0; j < win->info.cols; j++) {
      int index = i * win->info.rows + j;
      win->cells[index].isSelected = false;
    };
  };

  return;
};
