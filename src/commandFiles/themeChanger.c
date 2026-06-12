#include "../../include/command/command.h"
#include "../../include/lib/refresh.h"
#include "../../include/lib/warning.h"
#include "../../include/themes/customColors.h"
#include <form.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int themeChanger(win *w, char **cmd, int argc) {

  if (argc != 2) {
    SetWarning(w, "Usage : theme <theme name>", "", 0);
    return 1;
  }

  Theme theme;
  int length = strlen("themes/") + strlen(cmd[1]) + strlen(".toml") + 1;
  char *filename = malloc(sizeof(char) * length);

  strcpy(filename, "themes/");
  strcat(filename, cmd[1]);
  strcat(filename, ".toml");

  if (!loadTheme(filename, &theme, w->xterm)) {
    SetWarning(w, "Failed to load theme : ", cmd[1], 1);
    return 1;
  }
  customColors(theme, w->xterm);

  refreshWin1(w);
  refreshWin2(w);
  refreshWin4(w);

  free(filename);

  return 0;
}
