#include <cctype>

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
  } else if (cmd->type == 'y' || cmd->type == 'd'){ // copy line into buffer
    // calculate number of lines to yank
    count = std::min(static_cast<size_t>(count), filebuf.countLines() - curRow);
    clipboard.copyLines(filebuf, curRow, count); // copy lines to register
    if (cmd->type == 'y'){
      if (count > 1){
        rootStatus.setMessage(std::to_string(count) + " lines yanked"); // output message
      }
    } else if (cmd->type == 'd'){
      if (count > 1){
        rootStatus.setMessage(std::to_string(count) + " fewer lines");
      }
      filebuf.eraseLines(curRow,count);
      cursor.translate(std::max(curRow-1,0),0);
      tab.setCursor(cursor);
      if (filebuf.countLines() == 0){ // ensure file isn't empty
        filebuf.insertLines(0,1);
      }
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
        contents.pop_back();
        filebuf.insert(curRow+1,0,contents);
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
  } else if (cmd->type == 'r'){
    if (count + curCol <= static_cast<int>(filebuf.getLine(curRow).size())){
      // delete count characters 
      filebuf.erase(curRow,curCol,count);
      // insert the character
      if (cmd->data == '\n'){
        filebuf.insert(curRow,curCol,'\n');
        cursor.translate(curRow+1,0);
        rootStatus.reset();
      } else {
        filebuf.insert(curRow,curCol,std::string(count,cmd->data));
        cursor.setCol(curCol+count-1);
      }
      tab.setCursor(cursor);
    } 
  } else if (cmd->type == 'J'){ // join lines
    if (count == 1) {count = 2;} // J is 2J
    // join min(count, # of lines in file) together
    count = std::min(static_cast<size_t>(count), filebuf.countLines()-curRow);
    // join lines, trimming leading whitespace
    for (int i = 1; i < count; ++i){
      const auto& str = filebuf.getLine(curRow+i);
      // trim leading whitespace
      size_t j = 0; 
      while (j+1 < str.size() && isspace(str[j])){
        ++j;
      }
      if (j >= str.size()){ // do notohing for empty line 
        continue;
      }
      // append the line
      filebuf.append(curRow, ' ');
      // set cursor to char just before the new line joined
      cursor.setCol(filebuf.getLine(curRow).size()-1);
      while (j < str.size()-1){ 
        filebuf.append(curRow, str[j++]);
      }
    }
    filebuf.eraseLines(curRow+1,count-1);
    tab.setCursor(cursor);
  }
}
