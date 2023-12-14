
#include "comboNM_runner.h"

void ComboNMRunner::run(const ComboNM* cmd){ 
  // copy contents between movement into register
  // delete contents if the normal is a 'd' type
  
  auto& tab = activeWindow->getTabManager().curr();
  auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  const auto& normal = cmd->normal;
  const auto& movement = cmd->movement;
  // factor the count 
  int count = normalizeCount(normal.count) * normalizeCount(movement.count);
  
  // if movement is j,k, then convert into line-based commands
  if (movement.type == 'j'){
    Normal tmp{count+1, normal.type};
    normalRunner.run(&tmp);
    return;
  } else if (movement.type == 'k'){
    // calculate topline, and recalculate count
    int curline = cursor.getRow();
    int topline = std::max(0, curline-count);
    cursor.setRow(topline);
    tab.setCursor(cursor);
    Normal tmp{curline - topline + 1, normal.type};
    normalRunner.run(&tmp); 
    return;
  }  else if (movement.type == 'd') { // to forward dd commands
    Normal tmp{count, normal.type};
    normalRunner.run(&tmp);
    return;
  }
  
  // otherwise, execute the movement and calculate cursor positions
  Cursor beg = cursor;
  
  Movement tmp{movement}; tmp.count = count;
  movementRunner.run(&tmp);
  semiRunner.run(&tmp);
  matcherRunner.run(&tmp);
  searchRunner.run(&tmp);
  
  Cursor end = tab.getCursor();

  if (beg.getLoc() > end.getLoc()) { 
    // if movement goes backwards, swap beg and end
    std::swap(beg,end);
  }
  auto begCol = beg.getCol(), begRow = beg.getRow();
  // yank all chars in [beg,end)
  std::string contents;
  // swap beginning cursor with end if beg is after end
  // iterate through charbuf
  auto it = filebuf.begin(begRow, begCol); 
  while (it.getLoc() < end.getLoc()){
    contents.push_back(*it);
    ++it;
  }
  clipboard.set(false, contents);
  
  // delete if required
  if (normal.type == 'd'){ // erase if 'd'
    for (auto ch: contents) {
      if (ch == '\n'){ // join next line with ours
        filebuf.insert(begRow, begCol, filebuf.getLine(begRow+1));
        filebuf.eraseLines(begRow+1,2);
      } else {
        filebuf.erase(begRow, begCol, 1);
      }
    }
  }

  // calculate lines yanked/delete and print message
  size_t linecnt = end.getRow() - beg.getRow();
  if (linecnt > 1){
    if (normal.type == 'd'){
      rootStatus.setMessage(std::to_string(linecnt) + " fewer lines");
    } else {
      rootStatus.setMessage(std::to_string(linecnt) + " lines yanked");
    }
  }

  tab.setCursor(beg, true);  //set tab to beg, which is the smaller cursor
}
