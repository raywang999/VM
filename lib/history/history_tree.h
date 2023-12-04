#ifndef HISTORY_TREE_H
#define HISTORY_TREE_H

#include <chrono>
#include <memory>

#include "include/resetable.h"
#include "lib/tab/tab.h"

// stores undo branches as a history tree
// each node in the tree stores a deep-copy of the charbuf, and the cursor position
class HistoryTree: public Resetable {
  struct Node {
    int edit;
    const decltype(std::chrono::system_clock::now()) timestamp
      = std::chrono::system_clock::now();
    LinedCharbuf<char> file;
    Cursor cursor;
    Node* parent = nullptr;
    Node(const Tab& tab): 
      file{tab.getFilebuf()}, // slice the charbuf part of the filebuf
      cursor{tab.getCursor()} 
    {}
  };
  int edit = 0;
  Node root;
  Node* curr;
  std::vector<Node*> future; // stack of redo futures
  // all non-root nodes we have created
  std::vector<Node> store;
 public:
  HistoryTree(const Tab& tab): root{tab}, curr{&root} {}
  // undo most recent command. REturns true if successfully undo 
  bool undo() { 
    if (curr->parent) {
      curr = curr->parent;
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
  // pushes an new Tab onto the tree. Clears the future
  void push(const Tab& tab) {
    auto& newNode = store.emplace_back(tab);
    newNode.edit = ++edit;
    future.clear();
    newNode.parent = curr;
    curr = &newNode;
  }

  const Node* getCurr() const noexcept {return curr; }

};

#endif