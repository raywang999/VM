#ifndef NORMAL_PARSER_H
#define NORMAL_PARSER_H

#include <string>
#include <cctype>
#include <unordered_set>

#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

// parses basic normal mode commands 
class NormalParser: public CommandParser<Normal>{
  CountedParser countedParser;
  // holds the currently parsed normal command
  Normal theCommand{};
  // whether we need to parse another keystroke for e.g. cc, dd, yy
  bool parseData = false;

  // set storing which command types are terminals, i.e. don't need extra data
  inline static const std::unordered_set<int> terminalTypes{
    'a', 'i', 'o', 'p', 's', 'u', 'x', 
    'A', 'I', 'J', 'O', 'P', 'R', 'S', 'X', '.'
  };

  bool parse(const Keystroke& keystroke) override;
  void doReset() override { theCommand = Normal{}; parseData = false; countedParser.reset();}
 public: 
  const Normal* getCommand() const noexcept override {return &theCommand;};
};

#endif

