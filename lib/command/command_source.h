#ifndef COMMAND_SOURCE_H
#define COMMAND_SOURCE_H

#include "include/subject.h"
#include "lib/command/command.h"

// parameterize Command Sources by the Type of command they release
template<typename CommandType>
  requires std::derived_from<CommandType, Command>
class CommandSource; 

// specialize for base class CommandSource<Command>
template<>
class CommandSource<Command>: public Subject<Command, CommandSource<Command>> {
 public:
  virtual const Command* getCommand() const =0;
  using Subject_t = Subject<Command,CommandSource<Command>>;
  using Subject_t::notifyAll;
  using Subject_t::attach;
};


// parameterize Command Sources by the Type of command they release
template<typename CommandType>
  requires std::derived_from<CommandType, Command>
class CommandSource: 
  public Subject<CommandType, CommandSource<CommandType>>,
  public CommandSource<Command>
{ 
 public: 
  const CommandType* getCommand() const override =0;
  void notifyAll(){
    Subject<CommandType,CommandSource<CommandType>>::notifyAll(); 
    CommandSource<Command>::notifyAll();
  }
  using Subject_t = Subject<CommandType,CommandSource<CommandType>>;
  using Subject_t::attach;
  using CommandSource<Command>::attach;
};

#endif
