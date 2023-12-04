#ifndef COMMAND_RECORDER_H
#define COMMAND_RECORDER_H

#include <vector>
#include <memory>

#include "include/resetable.h"
#include "lib/command/runner/command_runner.h"
#include "lib/command/command_source.h"

// records the commands run so that they are accurrately played through Macros and Undo/Redo
// note: since the input commands expire, we need to copy them all
class CommandRecorder: 
  public CommandRunner<Normal>,
  public CommandRunner<Insert>, 
  public CommandRunner<Movement>, 
  public CommandRunner<Ex>,
  public CommandSource<Sequence>,
  public Resetable
{
  std::vector<std::unique_ptr<Command>> commandCopies;
  Sequence theSequence;
  bool active = true; // whether we listen for commands
  void doReset() override {theSequence.theSequence.clear(); active=true;}
 public:
  template<typename CommandType>
  // create a copy of cmd and add it to the sequence
  void add(const CommandType* cmd) {
    commandCopies.push_back(std::make_unique<CommandType>(*cmd));
    theSequence.theSequence.push_back(commandCopies.back().get());
  }
  // pops the last recorded command 
  void pop() { 
    theSequence.theSequence.pop_back();
    commandCopies.pop_back();
  }
  // if type is O or o, then delete the preceeding normal 
  // otherwise, join the preceeding normal in to a command sequence
  void run(const Insert* insert) override;
  void run(const Movement* move) override { add(move); }
  void run(const Ex* ex) override {add(ex);}
  void run(const Normal* normal) override {add(normal);}
  const Sequence* getCommand() const override {return &theSequence;}
  void setActive(bool type) noexcept {active = type;}
};

void inline CommandRecorder::run(const Insert* insert) {
  if (insert->mode != 'o' && insert->mode != 'O'){
    add(insert);
  }
}

#endif

