#ifndef CTRL_PARSER_H
#define CTRL_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

// parses ctrl commands 
class CtrlParser: public CommandParser{
  CountedParser countedParser{};
  // holds the currently parsed ctrl
  Ctrl theCommand;
  bool parse(const Keystroke& keystroke) override;
  void doReset() override { theCommand = Ctrl{1,0};}
 public: 
  const Ctrl* getCommand() const override {return &theCommand;};
};

#endif
