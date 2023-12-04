#include "undo_runner.h"
#include "include/utility.h"

void UndoRunner::run(const Normal* normal){
  if (normal->type != 'u') return;
  int cntChanges = 0;
  for (int i=0; i < normalizeCount(normal->count) && historyManager.undo(); ++i){
    ++cntChanges;
  }

}

void UndoRunner::run(const Ctrl* normal){

}
