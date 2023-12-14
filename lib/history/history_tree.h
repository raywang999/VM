#ifndef HISTORY_TREE_H_F
#define HISTORY_TREE_H_F

#include <chrono>
#include <vector>
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
    Node(int edit, const Tab& tab); 
  };
 private:
  int edit = 0;
  std::vector<int> future; // stack of redo futures
  // all non-root nodes we have created
  // root is stored at store[0]
  std::vector<Node> store;
  // currently active edit number
  int curr = 0;
  // check if filecontents and the current contents of the store are same
  bool same(const LinedFilebuf<char>& file);
 public:
  HistoryTree(const Tab& tab); 
  // undo most recent command. REturns true if successfully undo 
  bool undo(); 
  // redo most recent command. return true iff successful
  bool redo();
  // if tab's file contents changed, create a new edit
  // with cursor's beginnning poosition set to beg
  void push(const Tab& tab, const Cursor& beg);

  // get current edit 
  int getCurr() const noexcept { return curr; }
  const Node& getCurrNode() const noexcept {return store[curr]; }
  const Node& getNode(int edit) const noexcept {return store[edit]; }

};

#endif