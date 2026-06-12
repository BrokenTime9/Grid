#include "../../include/command/command.h"
#include "../../include/lib/refresh.h"
#include "../../include/lib/warning.h"
#include "../../include/themes/customColors.h"
#include "../../include/types.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;

} copyCellStruct;

typedef struct {
  copyCellStruct startCopy;
  copyCellStruct startPaste;

  copyCellStruct buf;

} pasteCellStruct;

void pasteCell(win *w, pasteCellStruct cell, int index);

void setColor(win *w, char **args, int argc) {
  if (argc != 6) {
    SetWarning(w, "Usafe : color <start-x start-y end-x end-y color-name>", "",
               0);
    return;
  }
  if (strlen(args[5]) != 7 || args[5][0] != '#') {
    SetWarning(w, "Wrong hex code entered : ", args[5], 1);
    return;
  }

  for (int i = 1; i <= 4; i++) {
    if (atoi(args[i]) < 0) {
      SetWarning(w, "Wrong Co-ordinates entered", "", 0);
      return;
    }
  }

  int index = atoi(args[2]) * w->win1.info.cols + atoi(args[1]);
  if (index >= w->win1.totalCells) {
    SetWarning(w, "Start Position Out of Range", "", 0);
    return;
  }

  index = atoi(args[4]) * w->win1.info.cols + atoi(args[3]);
  if (index >= w->win1.totalCells) {
    SetWarning(w, "End Position Out of Range", "", 0);
    return;
  }

  setCellColor(w, args);
  refreshWin1(w);
  refreshWin2(w);
}

void setCellColor(win *w, char **args) {
  int x1 = atoi(args[1]);
  int x2 = atoi(args[3]);
  int y1 = atoi(args[2]);
  int y2 = atoi(args[4]);

  int startX = x1 < x2 ? x1 : x2;
  int endX = x1 < x2 ? x2 : x1;
  int startY = y1 < y2 ? y1 : y2;
  int endY = y1 < y2 ? y2 : y1;
  int index;

  color color = hexTo3bit(args[5]);
  for (int i = startX; i <= endX; i++) {

    for (int j = startY; j <= endY; j++) {

      index = j * w->win1.info.cols + i;

      w->win1.cells[index].color = color;
      w->win1.tempCells[index].color = color;
      w->win1.cells[index].isSelected = true;
      w->win1.tempCells[index].isSelected = true;
    }
  }
};

void setCopy(win *w, char **args, int argc) {

  if (argc != 7) {
    SetWarning(w,
               "Usage : copy <copy-startx copy-starty copy-endx copy-endy "
               "paste-startx paste-starty >",
               "", 0);
    return;
  }

  for (int i = 1; i <= argc - 1; i++) {
    if (atoi(args[i]) < 0) {
      SetWarning(w, "Wrong Co-ordinates entered", "", 0);
      return;
    }
  }

  int index = atoi(args[2]) * w->win1.info.cols + atoi(args[1]);
  if (index >= w->win1.totalCells) {
    SetWarning(w, "Start Position Out of Range", "", 0);
    return;
  }

  index = atoi(args[4]) * w->win1.info.cols + atoi(args[3]);
  if (index >= w->win1.totalCells) {
    SetWarning(w, "End Position Out of Range", "", 0);
    return;
  }

  index = atoi(args[6]) * w->win1.info.cols + atoi(args[5]);
  if (index >= w->win1.totalCells) {
    SetWarning(w, "End Position Out of Range", "", 0);
    return;
  }

  copyCell(w, args);
  return;
}

void copyCell(win *w, char **args) {

  int x1 = atoi(args[1]);
  int y1 = atoi(args[2]);
  int x2 = atoi(args[3]);
  int y2 = atoi(args[4]);

  int x3 = atoi(args[5]);
  int y3 = atoi(args[6]);

  int copyStartX = x1 < x2 ? x1 : x2;
  int copyEndX = x1 < x2 ? x2 : x1;
  int copyStartY = y1 < y2 ? y1 : y2;
  int copyEndY = y1 < y2 ? y2 : y1;

  int pasteStartX = x3;
  int pasteStartY = y3;
  int index;

  for (int i = copyStartX; i <= copyEndX; i++) {
    for (int j = copyStartY; j <= copyEndY; j++) {
      index = j * w->win1.info.cols + i;
      pasteCell(w,
                (pasteCellStruct){.startCopy.x = copyStartX,
                                  .startCopy.y = copyStartY,
                                  .startPaste.x = pasteStartX,
                                  .startPaste.y = pasteStartY,
                                  .buf.x = i,
                                  .buf.y = j},
                index);
    }
  }

  refreshWin1(w);
  refreshWin2(w);
}

void pasteCell(win *w, pasteCellStruct cell, int index) {
  int pasteX = cell.startPaste.x + (cell.buf.x - cell.startCopy.x);
  int pasteY = cell.startPaste.y + (cell.buf.y - cell.startCopy.y);

  int pasteIndex = pasteY * w->win1.info.cols + pasteX;

  if (pasteX < 0 || pasteX >= w->win1.info.cols || pasteY < 0 ||
      pasteY >= w->win1.info.rows) {
    return;
  }

  w->win1.cells[pasteIndex].isSelected = w->win1.cells[index].isSelected;
  w->win1.cells[pasteIndex].color = w->win1.cells[index].color;

  w->win1.tempCells[pasteIndex].isSelected =
      w->win1.tempCells[index].isSelected;
  w->win1.tempCells[pasteIndex].color = w->win1.tempCells[index].color;
}
