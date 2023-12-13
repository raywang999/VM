#ifndef MACRO_PARSER_H
#define MACRO_PARSER_H

#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

// parses read/write Macro (i.e. q,@) commands 
class MacroParser: public CommandParser<Macro>{
  CountedParser countedParser;
  // holds the currently parsed macro 
  Macro theMacro;
  bool readRegister = false;
  bool isRecording = false;
  bool parse(const Keystroke& keystroke) override;
  void doReset() override { 
    countedParser.reset();
    readRegister = false;
  }
 public: 
  const Macro* getCommand() const override {return &theMacro;};
  void setIsRecording(bool val) noexcept {isRecording = val;}
};

#endif

