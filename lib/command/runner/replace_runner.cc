#include <string>
#include <algorithm>

#include "include/utility.h"
#include "replace_runner.h"

void ReplaceRunner::run(const Replace* cmd){
  int count = normalizeCount(cmd->count);
  std::string thecontents;
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  for (int i=0; i < count; ++i) {
    thecontents += cmd->sentence;
  }
  auto curCol = cursor.getCol(), curRow = cursor.getRow();
  filebuf.erase(curRow, curCol,thecontents.size());
  filebuf.insert(cursor.getRow(), cursor.getCol(), thecontents);
  // set new cursor location
  cursor.setCol(curCol + thecontents.size() - 1);
  tab.setCursor(cursor);
  modeManager.setMode(ModeType::Normal);
}

