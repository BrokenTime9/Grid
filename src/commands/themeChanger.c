
#include "../../include/command.h"
#include "../../include/customColors.h"
#include "../../include/refresh.h"
#include <form.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int themeChanger(char *cmd, win *w, char **warning) {
  Theme theme;
  int length = strlen("themes/") + strlen(cmd) + strlen(".toml") + 1;
  char *filename = malloc(sizeof(char) * length);

  strcpy(filename, "themes/");
  strcat(filename, cmd);
  strcat(filename, ".toml");

  if (!loadTheme(cmd, &theme)) {
    w->extras.warning = true;
    w->extras.warning = "Failed to load the theme";
    return 1;
  }
  customColors(theme);

  refreshWin1(w);
  refreshWin2(w);
  refreshWin4(w);

  return 0;
}
