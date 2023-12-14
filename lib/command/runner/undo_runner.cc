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
  auto& tree = historyManager.getTree(filename);
  int currEdit = tree.getCurr(), prevEdit = currEdit;
  for (int i=0; i < maxChanges && historyManager.undo(filename); ++i){
    ++cntChanges; prevEdit = currEdit; currEdit = tree.getCurr();
  }
  if (cntChanges == 0){
    rootStatus.setMessage("Already at oldest change");
  } else {
    persistChange();
    auto prev = &tree.getNode(prevEdit);
    setChangeMessage(cntChanges, startLineCnt, prev, true);
    tab.setCursor(prev->beg);
  }
}

// listen for Ctrl r
void UndoRunner::run(const Ctrl* cmd){
  if (cmd->type != 'r') return;
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  const auto& filename = filebuf.getFilename();
  int startLineCnt = filebuf.countLines();
  // total number of successful redos
  int cntChanges = 0;
  // aplly count number of undos, maximum by number of redos available in history 
  const auto maxChanges = normalizeCount(cmd->count);
  auto& tree = historyManager.getTree(filename);
  // last undone command
  for (int i=0; i < maxChanges && historyManager.redo(filename); ++i){
    ++cntChanges;
  }
  if (cntChanges == 0){
    rootStatus.setMessage("Already at newest change");
  } else {
    persistChange();
    auto currNode = tree.getCurrNode();
    setChangeMessage(cntChanges, startLineCnt, &currNode, false);
    tab.setCursor(currNode.end);
  }
}
