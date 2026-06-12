#ifndef RENDER_H
#define RENDER_H

#include "../types.h"

void gridRender(win *w);
void tempGridRender(win *w);
void sidebarRender(win *w);
void infoWinRender(win *w);

void colorControl(win *w, WINDOW *window, int t, cell c);

void resizeCell(win *w, int ch);
void updateStatusBar(win *w);

#endif
