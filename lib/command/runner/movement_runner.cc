#include "movement_runner.h"
#include "include/utility.h"

// the movement must be one of bfhjklnwFN^$0%;
void MovementRunner::run(const Movement* movement){
  using std::max;
  auto& tab = activeWindow->getTabManager().curr();
  const auto& filebuf = tab.getFilebuf();
  auto& cursor = tab.getCursor();
  auto col = cursor.getCol();
  auto row = cursor.getRow();
  // if don't use prev, the reset cursor col 
  if (!usePrev){ 
    usePrev = true; 
    prevCursorCol = cursor.getCol();
  }
  bool movementSuccess = true;
  if (movement->type == 'j' || movement->type == 'k'){
    int dr = movement->count; // delta row
    if (movement->type == 'k') {
      dr *= -1;
    }
    int newrow = row + dr;
    // ensure 0 <= newrow < # of lines in file
    newrow = min(newrow,filebuf.countLines()-1);
    newrow = max(newrow,0);
    // ensure 0 <= newcol < # of characters in the file
    int newcol = min(prevCursorCol, filebuf.getLine(newrow).size()-2);
    newcol = max(newcol, 0);
    if (newrow == row){ movementSuccess = false; } // failed to move
    else {
      cursor.setCol(newcol);
      cursor.setRow(newrow);
    }
  } else if(movement->type == 'l' || movement->type == 'h'){
    int dc = movement->count;
    if (movement->type == 'h') dc *= -1;
    auto newcol =  col + dc;
    newcol = min(newcol, filebuf.getLine(row).size()-2);
    newcol = max(0,newcol); 
    if (newcol == col){ movementSuccess = false; }
    else {
      prevCursorCol = newcol;
      cursor.setCol(newcol);
    }
  }
  if (movementSuccess){ activeWindow->render(); }
}
