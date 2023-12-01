#include "normal_runner.h"

void NormalRunner::run(const Normal* normal){
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto& cursor = tab.getCursor();
  if (insertDispatch.count(normal->type)){ 
    // switch to insert mode
    insertDispatch.at(normal->type)(this); 
    insertParser.setCount(normal->count);
    insertParser.setMode(normal->type);
    modeManager.setMode(ModeType::Insert);
    activeWindow->render();
  }
}
