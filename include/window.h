#ifndef WINDOW_H
#define WINDOW_H

#include "types.h"

void rootInit(win *w);
void winInit(win *window);
void sidebarWinInit(win *w, int h, int wid);

void updateStatusBar(win *window);

#endif // !WINDOW_H
