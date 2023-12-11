#include <cctype>

#include "movement_runner.h"
#include "include/utility.h"

// the movement must be one of bfhjklnwFN^$0%;
void MovementRunner::run(const Movement* movement){
  int count = normalizeCount(movement->count);
  using std::max;
  auto& tab = activeWindow->getTabManager().curr();
  const auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  auto col = cursor.getCol();
  auto row = cursor.getRow();
  // if don't use prev, the reset cursor col 
  if (!usePrev){ 
    usePrev = true; 
    prevCursorCol = cursor.getCol();
  }
  if (movement->type == 'j' || movement->type == 'k'){
    int dr = count; // delta row
    if (movement->type == 'k') {
      dr *= -1;
    }
    // ensure 0 <= newrow < # of lines in file
    int newrow = fit(0, static_cast<int>(filebuf.countLines())-1, row + dr);
    // ensure 0 <= newcol < # of characters in the file
    int newcol = min(prevCursorCol, filebuf.getLine(newrow).size()-2);
    newcol = max(newcol, 0);
    if (newrow != row){ 
      cursor.translate(newrow, newcol);
      tab.setCursor(cursor);
    }
  } else if(movement->type == 'l' || movement->type == 'h'){
    int dc = count;
    if (movement->type == 'h') dc *= -1;
    auto newcol =  col + dc;
    newcol = min(newcol, filebuf.getLine(row).size()-2);
    newcol = max(0,newcol); 
    if (newcol != col){ 
      prevCursorCol = newcol;
      cursor.setCol(newcol);
      tab.setCursor(cursor);
    }
  } else if (movement->type == '$'){
    int size = filebuf.getLine(row).size();
    cursor.setCol(std::max(0,size-2)); 
    tab.setCursor(cursor);
  } else if (movement->type == '^'){
    const auto& line = filebuf.getLine(row);
    size_t col = 0;
    while (col+1 < line.size() && isspace(line[col])){ 
      ++col;
    }
    cursor.setCol(col);
    tab.setCursor(cursor);
  } else if (movement->type == '0'){
    cursor.setCol(0); tab.setCursor(cursor);
  } else if (movement->type == 'f'){
    if (movement->seek == '\n') return; // don't seek for newline
    const auto& str = filebuf.getLine(row); 
    auto beg = str.begin() + col;
    auto end = str.end();
    auto pos = findNth(count, beg+1, end, movement->seek);
    if (pos != end){
      ptrdiff_t delta = pos - beg;
      cursor.setCol(col + delta);
      tab.setCursor(cursor);
    }
  } else if (movement->type == 'F'){
    const auto& str = filebuf.getLine(row); 
    auto beg = str.rbegin() + (str.size()-1) - col;
    auto end = str.rend();
    auto pos = findNth(count, beg+1, end, movement->seek);
    if (pos != end){
      ptrdiff_t delta = pos - beg;
      cursor.setCol(col - delta);
      tab.setCursor(cursor);
    }
  } else if (movement->type == 'w'){ 
    Chunkw matcher{}; // use W matcher
    auto end = filebuf.end();
    // find the start of the Nth word
    auto pos = findNth(count, filebuf.begin(row, col), end, matcher);
    setCursor(pos,end);
  } else if (movement->type == 'b'){ 
    Chunkb matcher{}; // use W matcher
    auto beg = ++filebuf.rbegin(row,col);
    auto end = filebuf.rend();
    // find the start of the Nth word
    auto pos = findNth(count, beg, end, matcher);
    setCursor(pos,end);
  } else if (movement->type == 'W'){ 
    ChunkW matcher{}; // use W matcher
    auto end = filebuf.end();
    // find the start of the Nth word
    auto pos = findNth(count, filebuf.begin(row, col), end, matcher);
    setCursor(pos,end);
  } else if (movement->type == 'B'){ 
    ChunkW matcher{};
    auto end = filebuf.rend();
    // find the start of the Nth word
    auto pos = findNth(count, filebuf.rbegin(row, col), end, matcher);
    setCursor(pos,end);
  }
}
