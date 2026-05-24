#ifndef WINDOW_H
#define WINDOW_H

#include "types.h"

void rootInit(win *w, int cols, int rows);
void winInit(win *window);
void sidebarWinInit(win *w, int h, int wid);

#endif // !WINDOW_H
