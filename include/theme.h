#ifndef THEME_H
#define THEME_H

typedef struct {
  char background[7];
  char text[7];
  char border[7];
  char cursor[7];
  char selected[7];
  char warning[7];
  char secondary[7];
} Theme;

int loadTheme(const char *path, Theme *theme);

#endif
