#ifndef MOVEMENT_PARSER_H
#define MOVEMENT_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

// parses basic normal mode commands 
class MovementParser: public CommandParser{
  CountedParser countedParser;
  // holds the currently parsed movement 
  Movement theCommand{};
  // whether we are reading the first character
  bool first = true;
  // whether we need to parse a second part of the movement 
  // i.e. for F_, f_
  bool parseSeek = false;
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

