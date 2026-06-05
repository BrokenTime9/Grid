#include "../include/cleanup.h"
#include <stdlib.h>

void quit(win *root) {
  if (root->popup)
    delwin(root->popup);

  if (root->win4)
    delwin(root->win4);

  if (root->win1.window)
    delwin(root->win1.window);

  if (root->win2.win)
    delwin(root->win2.win);

  if (root->root)
    delwin(root->root);

  if (root->win1.cells)
    free(root->win1.cells);

  endwin();
}
