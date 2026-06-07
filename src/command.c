
#include "../include/command.h"
#include "../include/customColors.h"
#include "../include/render.h"
#include <form.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void command(win *w) {
  int ch;
  char cmd[256] = {0};
  int len = 0;
  char *warning = NULL;

  keypad(w->cmd, TRUE);

  werase(w->win1.window);

  wresize(w->win1.window, w->rows - 1, w->cols * 75 / 100);

  if (w->extras.resize) {
    tempGridRender(&w->win1);
  } else {
    gridRender(&w->win1);
  }

  werase(w->cmd);

  mvwprintw(w->cmd, 0, 0, ":");

  while ((ch = wgetch(w->cmd)) != ERR) {
    switch (ch) {

    case KEY_BACKSPACE:
    case 127:
    case 8:
      if (len > 0) {
        cmd[--len] = '\0';
      }
      werase(w->cmd);

      mvwprintw(w->cmd, 0, 0, ":");
      mvwprintw(w->cmd, 0, 1, "%s", cmd);
      wrefresh(w->cmd);
      break;

    case 10:

      runCmd(cmd, len, w, &warning);
      wgetch(w->cmd);

      werase(w->cmd);
      box(w->cmd, 0, 0);

      wresize(w->win1.window, w->rows, w->cols * 75 / 100);

      if (w->extras.resize) {
        tempGridRender(&w->win1);
      } else {
        gridRender(&w->win1);
      }

      wrefresh(w->win1.window);
      wrefresh(w->cmd);

      len = 0;
      return;

    default:

      if (len < sizeof(cmd) - 1) {
        cmd[len++] = ch;
        cmd[len] = '\0';
      }

      mvwprintw(w->cmd, 0, 1, "%s", cmd);
      wrefresh(w->cmd);
      break;
    }
  }

  return;
}

void runCmd(char *cmd, int len, win *w, char **warning) {
  int preLen = 0;
  char *preCmd = malloc(sizeof(char) * 10);
  char *postCmd = malloc(sizeof(char) * 50);

  for (int i = 0; i < len; i++) {
    if (cmd[i] == ' ') {
      break;
    }
    preLen++;
  }

  strncpy(preCmd, cmd, preLen);
  preCmd[preLen] = '\0';

  strncpy(postCmd, cmd + preLen + 1, len - preLen - 1);
  postCmd[len - preLen - 1] = '\0';

  if (preLen != 5) {
    return;
  }

  if (preLen == 5) {

    if (cmp(preCmd, "theme")) {
      if (themeChanger(postCmd, w, warning)) {

        werase(w->cmd);

        wbkgd(w->cmd, COLOR_PAIR(secondaryBg));

        wattron(w->cmd, COLOR_PAIR(warn));
        mvwprintw(w->cmd, 0, 1, "%s", *warning);
        wattroff(w->cmd, COLOR_PAIR(warn));

        wrefresh(w->cmd);
      }
    }
    return;
  }
  return;
}

int cmp(char *str1, char *str2) { return !strcmp(str1, str2); }
