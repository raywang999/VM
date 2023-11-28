#ifndef MACRO_PARSER_H
#define MACRO_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

// parses read/write Macro (i.e. q,@) commands 
class MacroParser: public CommandParser{
  CountedParser countedParser;
  // holds the currently parsed macro 
  Macro theMacro;
  bool readRegister = false;
  bool parse(const Keystroke& keystroke) override;
  void doReset() override { 
    countedParser.reset();
    readRegister = false;
  }
 public: 
  const Macro* getCommand() const override {return &theMacro;};
};

#endif

