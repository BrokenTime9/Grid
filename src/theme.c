#include "../include/theme.h"
#include <stdio.h>
#include <string.h>

int loadTheme(const char *filename, Theme *theme) {
  FILE *fp = fopen(filename, "r");

  if (!fp) {
    perror("fopen");
    return 0;
  } else
    puts("opened");

  char line[128];

  while (fgets(line, sizeof(line), fp)) {

    char *start = strchr(line, '"');

    if (!start)
      continue;

    start++;

    if (strstr(line, "background")) {
      strncpy(theme->background, start, 6);
      theme->background[6] = '\0';
    }

    else if (strstr(line, "text")) {
      strncpy(theme->text, start, 6);
      theme->text[6] = '\0';
    }

    else if (strstr(line, "border")) {
      strncpy(theme->border, start, 6);
      theme->border[6] = '\0';
    }

    else if (strstr(line, "cursor")) {
      strncpy(theme->cursor, start, 6);
      theme->cursor[6] = '\0';
    }

    else if (strstr(line, "selected")) {
      strncpy(theme->selected, start, 6);
      theme->selected[6] = '\0';
    }

    else if (strstr(line, "warning")) {
      strncpy(theme->warning, start, 6);
      theme->warning[6] = '\0';
    }

    else if (strstr(line, "secondary")) {
      strncpy(theme->secondary, start, 6);
      theme->secondary[6] = '\0';
    }
  }

  fclose(fp);
  return 1;
}
