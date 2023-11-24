#ifndef MOVEMENT_PARSER_H
#define MOVEMENT_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/command_parser.h"
#include "lib/command/command.h"

// parses basic normal mode commands 
class MovementParser: public CommandParser{
  // holds the currently parsed movement 
  Movement theCommand{};
  // current status of the parser in form 00000tcf
  // f = parsing the first character 
  // c = parsing a count 
  // t = parsing the type (i.e. next should be parse seek)
  static constexpr char First = 1;
  static constexpr char Count = 2;
  static constexpr char Type = 4;
  char parseStatus = First;
  bool parse(const Keystroke& keystroke) override;
  void doReset() override { theCommand = Movement{}; parseStatus = First;}
 public: 
  Command getState() const override {return theCommand;};
};

#endif

