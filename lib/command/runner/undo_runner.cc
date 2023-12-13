#include "undo_runner.h"
#include "include/utility.h"

void UndoRunner::run(const Normal* normal){
  if (normal->type != 'u') return;
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  const auto& filename = filebuf.getFilename();
  int startLineCnt = filebuf.countLines();
  // total number of successful undos
  int cntChanges = 0;
  // aplly count number of undos, maximum by number of undos available in history 
  const auto maxChanges = normalizeCount(normal->count);
  auto tree = historyManager.getTree(filename);
  // last undone command
  const HistoryTree::Node* currNode = &tree.getCurrNode(), *prev = nullptr;
  for (int i=0; i < maxChanges && historyManager.undo(filename); ++i){
    prev = currNode; currNode = &tree.getCurrNode();
    ++cntChanges;
  }
  if (cntChanges == 0){
    rootStatus.setMessage("Already at oldest change");
  } else {
    persistChange();
    setChangeMessage(cntChanges, startLineCnt, prev, true);
    tab.setCursor(prev->beg);
  }
}

// listen for Ctrl r
void UndoRunner::run(const Ctrl* cmd){
  if (cmd->type != 'r') return;
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  // total number of successful undos
  int cntChanges = 0;
  // aplly count number of undos, maximum by number of undos available in history 
  const auto maxChanges = normalizeCount(cmd->count);
  for (int i=0; i < maxChanges && historyManager.redo(filebuf.getFilename()); ++i){
    ++cntChanges;
  }
  if (cntChanges == 0){
    rootStatus.setMessage("Already at newest change");
  } else {
    persistChange();
  }
}
