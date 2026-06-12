#include "../../include/command/command.h"
#include "../../include/lib/refresh.h"
#include "../../include/lib/warning.h"
#include <form.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void command(win *w) {
  int ch;
  char cmd[256] = {0};
  int len = 0;

  wresize(w->win[GRID], w->rows - 1, w->cols * 75 / 100);

  refreshWin1(w);

  werase(w->win[CMD]);

  mvwprintw(w->win[CMD], 0, 0, ":");

  while ((ch = wgetch(w->win[CMD])) != ERR) {
    switch (ch) {

    case KEY_BACKSPACE:
    case 127:
    case 8:
      if (len > 0) {
        cmd[--len] = '\0';
      }
      werase(w->win[CMD]);

      mvwprintw(w->win[CMD], 0, 0, ":");
      mvwprintw(w->win[CMD], 0, 1, "%s", cmd);
      wrefresh(w->win[CMD]);
      break;

    case 10:
      if (len <= 0) {

        werase(w->win[CMD]);
        wrefresh(w->win[CMD]);

        wresize(w->win[GRID], w->rows, w->cols * 75 / 100);
        refreshWin1(w);

        return;
      }

      runCmd(cmd, len, w);

      werase(w->win[CMD]);
      wrefresh(w->win[CMD]);

      wresize(w->win[GRID], w->rows, w->cols * 75 / 100);
      refreshWin1(w);

      len = 0;
      return;

    default:

      if (len < sizeof(cmd) - 1) {
        cmd[len++] = ch;
        cmd[len] = '\0';
      }

      mvwprintw(w->win[CMD], 0, 1, "%s", cmd);
      wrefresh(w->win[CMD]);
      break;
    }
  }

  return;
}

void runCmd(char *cmd, int len, win *w) {

  bool handled = false;
  int count = 0;

  char **cmds = cmdList(cmd, &count);

  if (strlen(cmds[0]) == 4) {
    if (cmp(cmds[0], "copy")) {
      setCopy(w, cmds, count);
      handled = true;
    }
  }

  if (strlen(cmds[0]) == 5) {
    if (cmp(cmds[0], "theme")) {
      themeChanger(w, cmds, count);
      handled = true;
    }

    if (cmp(cmds[0], "color")) {
      setColor(w, cmds, count);
      handled = true;
    }
  }

  if (!handled)
    SetWarning(w, "Invalid Command : ", cmds[0], 1);

  return;
}

int cmp(char *str1, char *str2) { return !strcmp(str1, str2); }
char **cmdList(char *list, int *count) {

  int iteration = 0;
  int pos = 0;
  int len = strlen(list);

  int start = 0;
  *count = 0;

  char **cmdList = malloc(10 * sizeof(char *));

  for (int i = 0; i <= len; i++) {
    if (list[i] == ' ' || list[i] == '\0') {
      int wordLen = i - start;

      if (wordLen > 0) {
        cmdList[*count] = malloc(wordLen + 1);

        strncpy(cmdList[*count], list + start, wordLen);
        cmdList[*count][wordLen] = '\0';

        (*count)++;
      }

      start = i + 1;
    }
  }
  return cmdList;
}
