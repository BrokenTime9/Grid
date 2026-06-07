#ifndef COMMAND_H
#define COMMAND_H

#include "./types.h"

void command(win *w);
void runCmd(char *cmd, int len, win *w, char **warning);
int cmp(char *str1, char *str2);

// commands -> in /src/commands
int themeChanger(char *cmd, win *w, char **warning);

#endif
