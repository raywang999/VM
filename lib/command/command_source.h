#ifndef COMMAND_SOURCE_H
#define COMMAND_SOURCE_H

#include "include/subject.h"
#include "lib/command/command.h"

// parameterize Command Sources by the Type of command they release
template<typename CommandType>
  requires std::derived_from<CommandType, Command>
class CommandSource: Subject<CommandType, CommandSource<CommandType>> { 
 public: 
  virtual const CommandType* getCommand() const =0;
  using Subject<CommandType, CommandSource<CommandType>>::attach;
  void notifyAll(){ Subject<CommandType, CommandSource<CommandType>>::notifyAll(this);};
};

#endif
