#ifndef RENDER_H
#define RENDER_H

#include "types.h"

void gridRender(win1 *w);
void tempGridRender(win1 *w);
void sidebarRender(win *w);
void infoWinRender(win *window);

void colorControl(WINDOW *w, int t, cell c);

void resizeCell(win *w, int ch);
void updateStatusBar(win *window);

#endif
