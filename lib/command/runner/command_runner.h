#ifndef COMMAND_RUNNER_H
#define COMMAND_RUNNER_H

#include "include/observer.h"
#include "lib/command/command_source.h"

// parameterize Command Sources by the Type of command they release
template<typename CommandType>
  requires std::derived_from<CommandType, Command>
class Observer<CommandSource<CommandType>>{
 public: 
  virtual void run(const CommandType*) =0;
  virtual void notify(const CommandSource<CommandType>& source){run(source.getCommand());}
  virtual ~Observer(){};
};

template<typename CommandType>
using CommandRunner = Observer<CommandSource<CommandType>>;

#endif
