#ifndef MODE_MODESTRUCT_H
#define MODE_MODESTRUCT_H

#include <vector>

#include "modetype.h"
#include "lib/command/command_runner.h"
#include "lib/command/command_parser.h"
#include "lib/keystroke/keystroke_consumer.h"

// Mode from which concrete Mode implementations extend
// forwards Emitted Commands to owned CommandRunners, and Keystrokes to owned Consumers
// also runs preConsume on keystroke, and terminates if unsuccessful
class Mode: public KeystrokeConsumer, public CommandSource {
  // the CommandParsers to which we forward keystrokes 
  // will be held in KeystrokeConsumer's subject class
  std::vector<CommandParser*> parsers;
  // the CommandRunners we forward emitted commands to 
  std::vector<CommandRunner*> runners;

  // Default behaviour of consuming a `Command` is
  // - call preConsume(Command) 
  // - if preConsume returns true, call all the CommandParsers we own 
  // - otherwise, don't call the CommandParsers
  void consume(const Keystroke& keystroke) override;

  // apply logic before we forward the keystroke to all parsers
  // return true if and only if you want to forward keystroke
  virtual bool preConsume(const Keystroke& keystroke){}
 public: 
  // add a CommandParser to the ones we own 
  // attach them to the runners we have, so that the commands are forwarded to them 
  template<typename... Args>
  void emplace_parser(Args&&... args);

  // add a Command Runner (not owned)
  // attach the runner to observe our Parsers
  void attach_runner(CommandRunner* runner);
};

inline void Mode::consume(const Keystroke& keystroke){
  if (preConsume(keystroke)) {
    for (auto parserp: parsers){ 
    }
  }
}

template<typename... Args>
void Mode::emplace_parser(Args&&... args){
  auto newParser = parsers.emplace_back(std::forward<Args>(args)...);
  for (auto runner: runners){
    newParser->attach(runner);
  }
}

// add a Command Runner (not owned)
// attach the runner to observe our Parsers
void Mode::attach_runner(CommandRunner* runner){
  runners.push_back(runner);
  for (auto parser: parsers){
    parser->attach(runner);
  }
}

#endif
