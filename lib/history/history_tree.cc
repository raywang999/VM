
#include "history_tree.h"

HistoryTree::Node::Node(int edit, const Tab& tab): edit{edit}, end{tab.getCursor()} {
  for (auto ch: tab.getFilebuf()){ // write all chars into contents
    contents.push_back(ch);
  }
}

bool HistoryTree::same(const LinedFilebuf<char>& file){
  if (file.countBytes() != store[curr].contents.size()) return false;
  size_t i = 0;
  for (auto ch: file){  
    if (store[curr].contents[i] != ch) return false;
    ++i;
  }
  return true;
}

HistoryTree::HistoryTree(const Tab& tab): store{Node{0,tab}}{}

bool HistoryTree::undo() { 
  if (curr) { // not the 0th change (i.e. root), so valid
    future.push_back(curr);
    curr = store[curr].parent;
    return true;
  }
  return false;
}
// redo most recent command. return true iff successful
bool HistoryTree::redo() { 
  if (future.empty()) return false;
  curr = future.back();
  future.pop_back();
  return true;
}
// if tab's file contents changed, create a new edit
// with cursor's beginnning poosition set to beg
void HistoryTree::push(const Tab& tab, const Cursor& beg) {
  if (same(tab.getFilebuf())){
    return; // do nothing if no change was made
  }
  // create a copy
  auto& newNode = store.emplace_back(++edit, tab);
  future.clear(); // clear redo chain
  newNode.parent = curr;
  newNode.beg = beg;
  curr = edit;
}
