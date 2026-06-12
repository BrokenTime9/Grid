#ifndef UNDO_H
#define UNDO_H

#include "../themes/theme.h"

typedef struct {
  int index;
  color oldColor;

} cellChanged;

typedef struct {
  color newColor;
  int cellAffected;

  cellChanged *cells;
} UndoCell;

typedef struct Command {

  UndoCell currentCommand;

  struct Command *nextCommand;
  struct Command *prevCommand;
} Command;

typedef struct {
  Command *head;
  Command *tail;
  Command *current;
} List;

#endif
