#ifndef CTRL_PARSER_H
#define CTRL_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/command_parser.h"
#include "lib/command/command.h"

// parses ctrl commands 
class CtrlParser: public CommandParser{
  // holds the currently parsed ctrl
  // ensure default count is 1, if parseStatus == First
  Ctrl theCommand{1,0};
  // current status of the parser in form 000000cf
  // f = parsing the first character 
  // c = parsing a count 
  static constexpr char First = 1;
  static constexpr char Count = 2;
  char parseStatus = First;
  bool parse(const Keystroke& keystroke) override;
  void doReset() override { theCommand = Ctrl{1,0}; parseStatus = First;}
 public: 
  Command getState() const override {return theCommand;};
};

#endif

