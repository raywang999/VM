#ifndef INSERT_RUNNER_H
#define INSERT_RUNNER_H

#include <string>

#include "lib/command/parser/insert_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"

// takes a completed Insert command and 
// - saves it to history 
// - applies multiplier n-1 times by repeatedly inserting text into the buffer
class InsertRunner: public CommandRunner{
  Window*& activeWindow;
  InsertParser& theParser;
  void notify(const Subject<Command*>&) override {
    Insert insert = *theParser.getCommand();
    std::string theInsert;
    for (int i=1; i < insert.count; ++i) {
      theInsert += insert.sentence;
    }
    theParser.reset();
    auto& tab = activeWindow->getTabManager().curr();
    auto& filebuf = tab.getFilebuf();
    auto& cursor = tab.getCursor();
    filebuf.insert(cursor.getRow(), cursor.getCol(), theInsert);
    cursor.setCol(cursor.getCol() + theInsert.size());
    activeWindow->render();
  }
 public:
  InsertRunner(Window*& activeWindow, InsertParser& parser): 
    activeWindow{activeWindow}, theParser{parser} {}
};

#endif

