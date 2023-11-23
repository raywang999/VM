#ifndef INSERT_PARSER_H
#define INSERT_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/command_parser.h"
#include "lib/command/command.h"

// parses basic normal mode commands 
class NormalParser: public CommandParser{
  // holds the currently parsed insert sequence 
  Normal theCommand{};
  // current status of the parser in form 00000tcf
  // f = parsing the first character 
  // c = parsing a count 
  // t = parsing the type (i.e. parse extra data)
  static constexpr int First = 1;
  static constexpr int Count = 2;
  static constexpr int Type = 4;
  char parseStatus = First;
  bool parse(const Keystroke& keystroke) override;
  void doReset() override { theCommand = Normal{}; parseStatus = 1;}
 public: 
  Command getState() const override {return theCommand;};
};

#endif

