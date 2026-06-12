#include "../../include/themes/customColors.h"
#include "../../include/types.h"
#include <stdlib.h>

void XtermColorPallete(win *w) {
  w->xterm = malloc(sizeof(color) * 256);
  mapColor(w->xterm);

  return;
}

void ThemeInit(win *w) {
  Theme theme;
  char *themefile = "themes/theme8.toml";

  if (!loadTheme(themefile, &theme, w->xterm)) {
    fprintf(stderr, "Failed to load theme\n");
    return;
  }

  customColors(theme, w->xterm);
}

void CommandInit(win *w) {
  w->commands.commandCap = 100;
  w->commands.commandCnt = 0;
  w->commands.currentCmd = 0;
  w->commands.command = malloc(sizeof(Command) * w->commands.commandCap);
  for (int i = w->commands.currentCmd; i < w->commands.commandCap; i++) {
    w->commands.command[i].isUsed = false;
  }
  return;
}
