#include "../../include/command/command.h"

void SetCommand(CmdList *list, Command cmd) {
  int currentCmd = list->currentCmd;
  list->command[currentCmd] = cmd;
  list->currentCmd++;
  list->commandCnt++;

  return;
}
void UnsetCommand() { return; }
void UndoColor() { return; }
