#ifndef MACRO_PARSER_H
#define MACRO_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/command_parser.h"
#include "lib/command/command.h"

// parses readMacro (i.e. @) commands 
class ReadMacroParser: public CommandParser{
  // holds the currently parsed macro 
  ReadMacro theCommand;
  static constexpr char First = 1;
  static constexpr char Count = 2;
  // current status of the parser in form 000000cf
  // f = parsing the first character 
  // c = parsing a count 
  char parseStatus = First;
  bool parse(const Keystroke& keystroke) override;
  void doReset() override { theCommand = ReadMacro{}; parseStatus = First;}
 public: 
  Command getState() const override {return theCommand;};
};

#endif

