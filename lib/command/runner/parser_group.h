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
  public CommandRunner<Command>,
  public KeystrokeConsumer
{ 
  // the array of CommandParsers
  std::vector<CommandParserBase*> parsers;
  // whether to continue forwarding keystrokes to the parsers
  bool continueForwarding = true;
 public: 
  // reset all resetables
  void run(const Command*){ 
    reset(); 
    continueForwarding = false;
  };

  // add a CommandParser to the group
  template<typename CommandType>
  void add(CommandParser<CommandType>* parser){
    parsers.push_back(parser);
  }
  // forward keystroke to parsers
  void consume(const Keystroke& keystroke) override { 
    bool allbroken = true;
    for (auto parser: parsers){
      if (!continueForwarding) break;
      parser->consume(keystroke);
      if (parser->isValid()) allbroken = false;
    }
    if (allbroken) reset();
    continueForwarding = true;
  }
  // reset all sub parsers
  void reset() { 
    for (auto parser: parsers){ parser->reset(); } 
    continueForwarding = true;
  }
};

#endif

