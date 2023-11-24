#ifndef NORMAL_PARSER_H
#define NORMAL_PARSER_H

#include <cctype>

#include "lib/command/command_parser.h"
#include "lib/command/command.h"

// helper class to parse optional numbers 
class CountedParser: public CommandParser{
  // holds the currently parsed count 
  int theCount;
  // current status of the parser in form 00000tcf
  // f = parsing the first character 
  // c = parsing a count 
  // r = let subclass parse the command. I.e. call doParse() 
  char parseStatus = First;
  static constexpr char First = 1;
  static constexpr char Count = 2;
  static constexpr char Type = 4;
  void doReset() override { theCommand = Normal{}; parseStatus = First;}

  // subclasses override this to parse the non-count portion of the command
  virtual bool doParse(const Keystroke& keystroke)=0; 

  // parses optional count. 
  // If no count, then set count to 1, use subclass parse 
  // if keystroke isn't a number, use subclass parse 
  bool parse(const Keystroke& keystroke) override;
 public: 
  Command* getState() const override {return theCommand.get();};
};

#endif

