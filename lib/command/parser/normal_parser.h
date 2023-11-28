#ifndef BASIC_NORMAL_PARSER_H
#define BASIC_NORMAL_PARSER_H

#include <string>
#include <cctype>

#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

// parses basic normal mode commands 
class BasicNormalParser: public CommandParser{
  CountedParser countedParser;
  // holds the currently parsed normal command
  Normal theCommand{};
  // whether we need to parse another keystroke for e.g. cc, dd, yy
  bool parseData = false;

  bool parse(const Keystroke& keystroke) override;
  void doReset() override { theCommand = Normal{}; parseData = false; countedParser.reset();}
 public: 
  const Normal* getCommand() const noexcept override {return &theCommand;};
};

#endif

