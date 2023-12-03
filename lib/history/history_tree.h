#ifndef HISTORY_TREE_H
#define HISTORY_TREE_H

#include <chrono>
#include <memory>

#include "include/resetable.h"
#include "lib/tab/tab.h"
#include "lib/command/command_recorder.h"
#include "lib/command/runner/general_runner.h"

// stores undo branches as a history tree
// each node in the tree stores a deep-copy of the Tab right after changes complete
class HistoryTree: public Resetable {
  struct Node {
    const decltype(std::chrono::system_clock::now()) timestamp
      = std::chrono::system_clock::now();
    std::unique_ptr<LinedFilebuf<char>> file;
    Tab tab{file.get()};
    std::vector<Node*> children;
    Node* parent = nullptr;
    Node(const Tab& tab): file{std::make_unique<LinedFilebuf<char>>(tab.getFilebuf())} {
      this->tab.setCursor(tab.getCursor());
    }
  };
  Node root;
  Node* curr;
  // all nodes we have created
  std::vector<Node> store;
 public:
  // undo most recent command 
  void undo() { 
    const auto& seq = past.getCommand()->theSequence;
    if (undos >= seq.size()) return; // do nothing if nothing to undo
    runner.run(seq[undos]);
  }
  // redo most recent command
  void redo() { 
    if (undos > 0 ) {
      --undos; 
      runner.run(past.getCommand()->theSequence[undos]);
    }
  }
};

#endif