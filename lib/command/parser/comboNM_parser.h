#ifndef COMBONM_PARSER_H
#define COMBONM_PARSER_H

#include <string>
#include <cctype>
#include <unordered_set>

#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/parser/movement_parser.h"

#include "lib/command/runner/command_runner.h"

// parses basic normal mode commands 
class ComboNMParser: 
  public CommandParser<ComboNM>, 
  // allow ourself to forward ourselves when movementParser emites
  public CommandRunner<Movement> 
{
  CountedParser countedParser;
  // help parse movement part
  MovementParser movementParser; 
  // holds the currently parsed ComboNM command
  ComboNM theCommand{};
  bool parseNormal = true; // whether we are still parsing the normal

  bool parse(const Keystroke& keystroke) override;
  void doReset() override { 
    theCommand = ComboNM{}; 
    parseNormal = true; 
    countedParser.reset();
    movementParser.reset();
  }
  // returns true for operations  with potential movement second part
  bool isNormDup(int ch){
    return ch == 'd' || ch == 'y';
  }

 public: 
  ComboNMParser(){ movementParser.attach(this); }
  void run(const Movement* cmd) override;
  const ComboNM* getCommand() const noexcept override {return &theCommand;};
};

#endif

