#include "../../include/lib/export.h"
#include <stdio.h>

void exportCoords(win *w) {
  FILE *fp = fopen("./Out/coords.txt", "w");

  if (!fp) {
    perror("fopen");
    return;
  }

  for (int i = 0; i < w->win1.totalCells; i++) {
    if (w->win1.cells[i].isSelected) {
      int cellNo = i;
      int cellTlx = w->win1.cells[i].info.tl.x;
      int cellTly = w->win1.cells[i].info.tl.y;
      int cellBrx = w->win1.cells[i].info.br.x;
      int cellBry = w->win1.cells[i].info.br.y;
      color cellColor = w->win1.cells[i].color;

      fprintf(fp, "%d -\n", cellNo);
      fprintf(fp, "\ttopleft - %d  %d\n", cellTlx, cellTly);
      fprintf(fp, "\tbottomright %d %d \n\n", cellBrx, cellBry);
      fprintf(fp, "\tcolor : r: %d g: %d  b: %d\n\n", cellColor.r, cellColor.g,
              cellColor.b);
    }
  }

  fclose(fp);
}
