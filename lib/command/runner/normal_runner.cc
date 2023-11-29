#include "normal_runner.h"

void NormalRunner::run(const Normal* normal){
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto& cursor = tab.getCursor();
  if (normal->type == 'i') { // entery insert mode
    theNormalMode.setMode(ModeType::Insert);
    insertParser.setCount(normal->count);
    theNormalMode.notifyAll();
  }
}
