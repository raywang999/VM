#include "include/utility.h"
#include "normal_runner.h"

void NormalRunner::run(const Normal* cmd){
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  auto curRow = cursor.getRow();
  auto curCol = cursor.getCol();
  int count = normalizeCount(cmd->count);

  if (cmd->type == 'x'){
    filebuf.erase(curRow,curCol,count);
    tab.fixCursor();
  } else if (cmd->type == 'X'){
    auto delCnt = min(count,curCol);
    filebuf.erase(curRow,curCol - delCnt, delCnt);
    cursor.setCol(curCol-delCnt);
    tab.setCursor(cursor);
  } else if (cmd->type == 'd'){ // run dd command
    
  } else {

  }
}
