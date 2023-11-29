#ifndef PARSER_GROUP_H
#define PARSER_GROUP_H

#include <vector>

#include "include/resetable.h"
#include "lib/command/runner/command_runner.h"
#include "lib/command/parser/command_parser.h"

// creates a group of Parsers 
// resets them all when one of them notifies
// note: should be attached after all other CommandRunners have been attached
class ParserGroup: 
  virtual public CommandRunner<Command>
{ 
  std::vector<Resetable*> resetables;
 public: 
  // reset all resetables
  void run(const Command*){ reset(); };

  // add a resetable to the group
  void add(Resetable* resetable){resetables.push_back(resetable);}
  void reset() { for (auto resetable: resetables){ resetable->reset(); }
  }
};

#endif

