#ifndef COMMAND_H
#define COMMAND_H

#include "../types.h"

void command(win *w);
void runCmd(char *cmd, int len, win *w);

int cmp(char *str1, char *str2);
char **cmdList(char *list, int *count);

// commands -> in /src/commands
int themeChanger(win *w, char **args, int argc);
void setColor(win *w, char **args, int argc);
void setCopy(win *w, char **args, int argc);

// helpers
void setCellColor(win *w, char **args);
void copyCell(win *w, char **args);

#endif
