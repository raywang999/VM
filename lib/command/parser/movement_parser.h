#ifndef MOVEMENT_PARSER_H
#define MOVEMENT_PARSER_H

#include <string>
#include <cctype>
#include <unordered_set>

#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

// parses basic normal mode commands 
class MovementParser: public CommandParser<Movement>{
  CountedParser countedParser;
  // holds the currently parsed movement 
  Movement theCommand{};
  // whether we are reading the first character
  bool first = true;
  // whether we need to parse a second part of the movement 
  // i.e. for F_, f_
  bool parseSeek = false;

  // set storing which command types are terminals, i.e. don't need extra seek
  static inline const std::unordered_set<int> terminalTypes{
    'b', 'h', 'j', 'k', 'l', 'n', 'w', 
    'N', '^', '$', '0', '%', ';'
  };

  bool parse(const Keystroke& keystroke) override;
  void doReset() override { 
    theCommand = Movement{}; 
    first = true; parseSeek = false;
    countedParser.reset();
  }
 public: 
  const Movement* getCommand() const override {return &theCommand;};
};

#endif

