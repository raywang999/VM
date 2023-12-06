#ifndef HISTORY_TREE_H
#define HISTORY_TREE_H

#include <chrono>
#include <memory>
#include <string>

#include "lib/tab/tab.h"

// stores undo branches as a history tree
// each node in the tree stores a deep-copy of the charbuf, and the cursor position
class HistoryTree {
 public:
  struct Node {
    using timestamp_t = decltype(std::chrono::system_clock::now());
    int edit;
    const timestamp_t timestamp = std::chrono::system_clock::now();
    std::string contents;
    Cursor beg; // cursor location before the change
    Cursor end; // cursor location after the change
    int parent;
    Node(int edit, const Tab& tab): edit{edit}, beg{tab.getCursor()} {
      for (auto ch: tab.getFilebuf()){ // write all chars into contents
        contents.push_back(ch);
      }
    }
  };
 private:
  int edit = 0;
  std::vector<int> future; // stack of redo futures
  // all non-root nodes we have created
  // root is stored at store[0]
  std::vector<Node> store;
  // currently active edit number
  int curr = 0;
  // check if filecontents and the string have same contents
  bool same(const std::string& str, const LinedFilebuf<char>& file){
    if (file.countBytes() != store[curr].contents.size()) return false;
    size_t i = 0;
    for (auto ch: file){  
      if (store[curr].contents[i] != ch) return false;
      ++i;
    }
    return true;
  }
 public:
  HistoryTree(const Tab& tab): store{Node{0,tab}}{}
  // undo most recent command. REturns true if successfully undo 
  bool undo() { 
    if (curr) { // not the 0th change (i.e. root), so valid
      future.push_back(curr);
      curr = store[curr].parent;
      return true;
    }
    return false;
  }
  // redo most recent command. return true iff successful
  bool redo() { 
    if (future.empty()) return false;
    curr = future.back();
    future.pop_back();
    return true;
  }
  // if tab's file contents changed, create a new edit
  // with cursor's beginnning poosition set to beg
  void push(const Tab& tab, const Cursor& beg) {
    if (same(store[curr].contents, tab.getFilebuf())){
      return; // do nothing if no change was made
    }
    // create a copy
    auto& newNode = store.emplace_back(++edit, tab);
    future.clear(); // clear redo chain
    newNode.parent = curr;
    newNode.beg = beg;
    curr = edit;
  }


  // get current edit 
  const int getCurr() const noexcept {return curr; }
  const Node& getCurrNode() const noexcept {return store[curr]; }

};

#endif