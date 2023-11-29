#ifndef INSERT_RUNNER_H
#define INSERT_RUNNER_H

#include <string>

#include "lib/command/parser/insert_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"

// takes a completed Insert command and 
// - applies multiplier by repeatedly inserting text into the buffer
class InsertRunner: public CommandRunner<Insert>{
  Window*& activeWindow;
  InsertParser& theParser;
 public:
  // handle insert command from user typing
  void notify(const CommandSource<Insert>&) override {
    auto command = Insert{*theParser.getCommand()};
    // the user already typed a copy of the insert, so only need to run count-1
    --command.count;
    run(&command);
  }
  void run(const Insert*) override;
  InsertRunner(Window*& activeWindow, InsertParser& parser): 
    activeWindow{activeWindow}, theParser{parser} {}
};

#endif

