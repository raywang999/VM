#ifndef COMMAND_SOURCE_H
#define COMMAND_SOURCE_H

#include "include/subject.h"
#include "lib/command/command.h"

class CommandSource: public Subject<Command*> { 
 public: 
  virtual const Command* getCommand() const =0;
};

#endif
