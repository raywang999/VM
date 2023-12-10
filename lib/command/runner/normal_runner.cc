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
  } else if (cmd->type == 'y'){ // run yy command
    // calculate number of lines to yank
    count = std::min(static_cast<size_t>(count), filebuf.countLines() - curRow);
    clipboard.copyLines(filebuf, curRow, count); // copy lines to register
    if (count > 1){
      rootStatus.setMessage(std::to_string(count) + " lines yanked"); // output message
    }
  } else if (cmd->type == 'p' || cmd->type == 'P') { 
    const auto& data = clipboard.get();
    // generate what to insert based on count
    std::string contents;
    for (int i = 0; i < count; ++i){
      contents.append(data.contents);
    }
    // we should insert newline first
    if (data.startNewLine ){ 
      if (cmd->type == 'p'){
        filebuf.insertLines(curRow+1,1); // start pasting from line after curRow
        // paste but ommit the last `\n`
        filebuf.insert(curRow+1,0,data.contents.substr(0,data.contents.size()-1));
        // calculate cursor position
        cursor.translate(curRow+1,0);
      } else {
        // note that contents will end with required '\n's 
        filebuf.insert(curRow,0,contents);
        cursor.setCol(0); // reset cursor
        tab.setCursor(cursor);
      }
      tab.setCursor(cursor);
    } else { // print without new line
      if (cmd->type == 'p'){ // move starting cursor one stop right
        curCol = filebuf.getLine(curRow).empty() ? 0 : curCol+1;
      }
      filebuf.insert(curRow, curCol, contents);
      if (contents.find('\n') == std::string::npos){ 
        // move cursor to end of insert sequence if no newlines were added
        cursor.setCol(curCol+contents.size()-1);
      }
      tab.setCursor(cursor);
    }
  } 
}
